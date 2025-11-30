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

//need to figure out how to draw this...
void DrawGrid(Grid* grid)
{
	for (float i = grid->minBound.x; i <= (float)grid->maxBound.x + grid->spacing; i += grid->spacing)
	{
		DrawLineEx({ 0, i }, { grid->maxBound.x - grid->minBound.x + grid->spacing, i }, 1.0f, BLUE);
		DrawLineEx({ i, 0 }, { i, grid->maxBound.x - grid->minBound.x + grid->spacing}, 1.0f, BLUE);
	}
}