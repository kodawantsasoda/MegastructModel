#include "SpatialGrid.h"

float sat(float x) {
	if (x < 0.0f) return 0.0f;
	if (x > 1.0f) return 1.0f;
	return x;
}

void InitGrid(Grid* grid, Vector2 minBound, Vector2 maxBound, float dimension)
{
	grid->minBound = minBound;
	grid->maxBound = maxBound;
	grid->dimension = dimension;
	grid->spacing = (maxBound.x - minBound.x) / (dimension);
}

int GetIndex(Grid* grid, Vector2 pos) 
{
	float x = sat((pos.x - grid->minBound.x) / (grid->maxBound.x - grid->minBound.x));
	float y = sat((pos.y - grid->minBound.y) / (grid->maxBound.y - grid->minBound.y));
	
	x = floor(x * (grid->dimension));
	y = floor(y * (grid->maxBound.y / grid->spacing));
	
	return grid->dimension * y + x;
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
		if (colTemp > colMax)
		{
			colTemp = colMin;
			rowTemp++;
		}
		DrawRectangle((colTemp * grid->spacing), rowTemp * grid->spacing, grid->spacing, grid->spacing, yellow);
		colTemp++;
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