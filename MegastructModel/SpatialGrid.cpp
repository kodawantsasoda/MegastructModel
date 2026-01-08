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
	//Insert(entity);
}

void Insert(Grid* grid, Entity* entity)
{
	Vector2 maxPos = { entity->collider.x + entity->collider.width, entity->collider.y + entity->collider.height };
	int minIndex = GetIndex(grid, entity->pos);
	int maxIndex = GetIndex(grid, maxPos);

	int rowMin = int(minIndex / grid->dimension);
	int colMin = minIndex % (int)grid->dimension;
	int rowMax = int(maxIndex / grid->dimension);
	int colMax = maxIndex % (int)grid->dimension;

	int dimension = (rowMax - rowMin + 1) * (colMax - colMin + 1);
	Color yellow = { 255, 255, 0, 100 };

	int colTemp = colMin;
	int rowTemp = rowMin;

	for (int i = 0; i < dimension; i++)
	{
		int currentGridIndex = i * colTemp + rowTemp;

		if (colTemp > colMax)
		{
			colTemp = colMin;
			rowTemp++;
		}
		//TODO:: will have to adjust this... we get data loss going from float to int
		DrawRectangle(colTemp * (int)grid->spacing, rowTemp * (int)grid->spacing, (int)grid->spacing, (int)grid->spacing, yellow);

		//do some arena/linked list work...
		/*what i need to do... so in the spatial hash grid we have cells. 
		each index in the cell holds a head pointer to a linked list of all clients within that cell. 
		and then each client holds an array of all cells it is occupying 
		im not using an array, ill probably use a contigious linked list so it can grow dynamically... this will be helpful if the entity
		shrinks and stuff too. i need an arena that is enough memory to store all entities cell belongings. so when i insert a client,
		ill reserve a spot in memory big enough to hold (possibly, depending on space...) every index in the spatial hash grid. so each
		entity requests space in the arena of sizeof(maximum cells * entityID(int))) 
		*/
		if (grid->cells[currentGridIndex]->entityIndex != -1)
		{
			//grid->cells[currentGridIndex]->entityIndex = entity->eBase.index;
			//arena alloc??
			//grid->cells[currentGridIndex]->next = entity->eBase.index;
			//grid->arena.previousOffset 
		
			//pushing the head to the tail essentially
			grid->cells[currentGridIndex]->next = grid->cells[currentGridIndex];
			grid->cells[currentGridIndex] = arenaGetBlock(&arena, sizeof)

		}
		else
		{
			//start of new cell.. arena alloc a new block of memory for the cell to use...
			//note that max entities in cell is not a hard rule... you can go over it just may not end up being sequential after you go over
			grid->cells[currentGridIndex] = (Cell*)arenaAlloc(&grid->arena, MAX_ENTITIES_IN_CELL * sizeof(grid->cells[currentGridIndex]));
			grid->cells[currentGridIndex]->entityIndex = entity->eBase.index;
			grid->cells[currentGridIndex]->next = NULL;
		}
		colTemp++;
	}

	//TODO: may need to store a min and max of the entities cells for updating and such
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