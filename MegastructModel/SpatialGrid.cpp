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
}

void InitGrid(Grid* grid, Vector2 minBound, Vector2 maxBound, float dimension)
{
	grid->minBound = minBound;
	grid->maxBound = maxBound;
	grid->dimension = dimension;
	grid->spacing = (maxBound.x - minBound.x) / (dimension);

	arena_init(&grid->arena, grid->backing_buffer, MAX_ENTITIES * sizeof(grid->cells));

	Cell cell;
	InitCell(&cell);
	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid->cells[i] = NULL;
	}
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

void Insert(Grid* grid, Entity* entity)
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
				grid->cells[currentGridIndex] = cell;
			}
			//placing new head of list
			else
			{
				cell->entityIndex = entity->eBase.index;
				cell->next = grid->cells[currentGridIndex];
				grid->cells[currentGridIndex] = cell;
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
		return;
	}
	//need to add remove
	Insert(grid, entity);
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