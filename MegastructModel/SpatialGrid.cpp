#include "SpatialGrid.h"

int32_t index1d(Grid* grid, float ordinate)
{
	return (int32_t)floor(ordinate / grid->dimension);
}
float position1dLow(Grid* grid, int32_t index)
{
	return (float)index * grid->dimension;
}
Vector2 index2d(Grid* grid, Vector2 pos)
{
	Vector2 translation = { index1d(grid, pos.x), index1d(grid, pos.y) };
	return translation;
}


void InitGrid(Grid* grid, Vector2 minBound, Vector2 maxBound, float dimension)
{
	grid->minBound = minBound;
	grid->maxBound = maxBound;
	grid->dimension = dimension;
}

float sat(float x) {
	if (x < 0.0f) return 0.0f;
	if (x > 1.0f) return 1.0f;
	return x;
}

int GetIndex(Grid* grid, Vector2 pos) 
{
	float x = (pos.x - grid->minBound.x) / (grid->maxBound.x - grid->minBound.x);
	int y = (pos.y - grid->minBound.y) / (grid->maxBound.y - grid->minBound.y);
	
	x = floor(x * (grid->dimension - 1));
	
	return x;
}

void DrawGrid(Grid* grid)
{
	for (int i = grid->minBound.x; i < grid->maxBound.x; i += grid->dimension)
	{
		DrawLine(0, i, grid->maxBound.x - grid->minBound.x, i, WHITE);
		DrawLine(i, 0, i, grid->maxBound.y - grid->minBound.y, WHITE);
	}
}