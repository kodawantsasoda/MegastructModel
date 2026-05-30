#include "SpatialGrid.h"

float sat(float x) {
	if (x < 0.0f) return 0.0f;
	if (x > 1.0f) return 1.0f;
	return x;
}

void InitCell(Cell* cell)
{
	cell->entityIndex = -1;
	cell->next = NULL;
	cell->prev = NULL;
}

void InitGrid(Grid* grid, Vector2 minBound, Vector2 maxBound, float dimension)
{
	grid->minBound = minBound;
	grid->maxBound = maxBound;
	grid->dimension = dimension;
	grid->spacing = (maxBound.x - minBound.x) / (dimension);
	grid->arena = { 0 };

	arena_init(&grid->arena, &grid->backing_buffer, sizeof(Cell) * 4);

	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid->cells[i] = NULL;
	}
	/*for (int i = 0; i < MAX_ENTITIES * sizeof(Cell) * GRID_SIZE; i++)
	{
		grid->backing_buffer[i] = 0;
	}*/
}

int GetIndex(Grid* grid, Vector2 pos) 
{
	float x = sat((pos.x - grid->minBound.x) / (grid->maxBound.x - grid->minBound.x));
	float y = sat((pos.y - grid->minBound.y) / (grid->maxBound.y - grid->minBound.y));
	
	x = (float)floor(x * (grid->dimension));
	y = (float)floor(y * (grid->maxBound.y / grid->spacing));
	
	//TODO::may need to adjust as we are having loss of data
	return (int)grid->dimension * (int)y + (int)x;
}

void NewClient(Entity* entity)
{
	entity->colliderId = -1;
}

void InsertEntityInGrid(Grid* grid, Entity* entity)
{
	Vector2 maxPos = { entity->collider.x + entity->collider.width, entity->collider.y + entity->collider.height };
	int minIndex = GetIndex(grid, entity->pos);
	int maxIndex = GetIndex(grid, maxPos);
	entity->cellMin = minIndex;
	entity->cellMax = maxIndex;

	int rowMin = int(minIndex / grid->dimension);
	int colMin = minIndex % (int)grid->dimension;
	int rowMax = int(maxIndex / grid->dimension);
	int colMax = maxIndex % (int)grid->dimension;

	int dimension = (rowMax - rowMin + 1) * (colMax - colMin + 1);
	Color yellow = { 255, 255, 0, 100 };

	int colTemp = colMin;
	int rowTemp = rowMin;

	int currentGridIndex = minIndex;

	//we need to iterate in order to add THE SAME ENTITY to MULTIPLE CELLS in the spatial hash grid
	for (int i = 0; i < dimension; i++)
	{
		if (colTemp > colMax)
		{
			colTemp = colMin;
			rowTemp++;
			currentGridIndex = minIndex + (int)grid->dimension;
		}

		entity->cells[i] = currentGridIndex;

		//TODO:: will have to adjust this... we get data loss going from float to int
		//DrawRectangle(colTemp * (int)grid->spacing, rowTemp * (int)grid->spacing, (int)grid->spacing, (int)grid->spacing, yellow);

		Cell* cell = (Cell*)arenaAlloc(&grid->arena, sizeof(Cell));
		if (!cell)
		{
			printf("Error on Insert function for Spatial Hash Grid... arena is out of space?\n");
		}
		else 
		{
			//if the cell does not have a head node attached to it
			if (!grid->cells[currentGridIndex])
			{
				cell->entityIndex = entity->eBase.index;
				cell->next = NULL;
				cell->prev = NULL;
				grid->cells[currentGridIndex] = cell;
			}
			//placing new head of list
			else
			{
				cell->next = grid->cells[currentGridIndex];
				cell->entityIndex = entity->eBase.index;
				cell->prev = NULL;
				cell->next->prev = cell;
				grid->cells[currentGridIndex] = cell;
				 //corruption begins here!!!!!!!!!!!!!!!!!
			}
		}
		
		colTemp++;
		currentGridIndex++;
	}

	//TODO: may need to store a min and max of the entities cells for updating and such
}

void UpdateClient(Grid* grid, Entity* entity)
{
	Vector2 maxPos = { entity->collider.x + entity->collider.width, entity->collider.y + entity->collider.height };
	int minIndex = GetIndex(grid, entity->pos);
	int maxIndex = GetIndex(grid, maxPos);

	//no change needed
	if (entity->cellMin == minIndex && entity->cellMax == maxIndex)
	{
		printf("No change\n");
		return;
	}
	printf("Change\n");
	//need to add remove
	InsertEntityInGrid(grid, entity);
}

void RemoveEntityInGrid(Grid* grid, Entity* entity)
{
	for (int i = 0; i < MAX_ENTITY_CELL_SIZE; i++)
	{

		//current cell in entity cell array
		int cellIndex = entity->cells[i];

		if (cellIndex == -1)
		{
			//all cells accounted for, we're done and exit
			return;
		}

		Cell* cell = grid->cells[cellIndex];

		if (!cell)
		{
			printf("Error on removing entity from spatial hash grid");
			return;
		}

		while (cell)
		{
			if (cell->entityIndex == entity->eBase.index)
			{
				//cell's previous pointer to another is NULL, so its at the head of the linked list
				if (!cell->prev)
				{
					//no next value of head of linked list
					if (!cell->next)
					{
						grid->cells[cellIndex] = NULL;
						return;
					}
					cell->next->prev = NULL;
					grid->cells[cellIndex] = cell->next;
					//FREE it from the arena
					//grid.arena->arenaDealloc(&grid->arena, (void*)cell, sizeof(Cell));
					arenaDealloc(&grid->arena, cell, sizeof(Cell));
					cell = NULL;
				}
				if (cell->prev)
				{
					//delete stuff which means point pointers to other stuff and take out this bad boy... might need to add a previous node??
					cell->prev->next = cell->next;
					cell->next->prev = cell->prev;
				}
			}
			cell = cell->next;
		}
		//entity->cells[i] = -1; //maybe? if we keep this we need to change zeroEntity Init in entity.h
		//what we also need to do is have a free list of spots in our arena in order to gain some memory back...
	}
}

//need to figure out how to draw this...
void DrawGrid(Grid* grid)
{
	for (float i = grid->minBound.x; i <= (float)grid->maxBound.x + grid->spacing; i += grid->spacing)
	{
		DrawLineEx({ 0, i }, { grid->maxBound.x - grid->minBound.x + grid->spacing, i }, 1.0f, BLUE);
		DrawLineEx({ i, 0 }, { i, grid->maxBound.x - grid->minBound.x + grid->spacing}, 1.0f, BLUE);
	}
}