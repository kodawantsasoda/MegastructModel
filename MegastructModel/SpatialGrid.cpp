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


Grid InitGrid(Vector2 startPos, Vector2 endPos, float spacing)
{

}

void DrawGrid(Grid* grid, int screenWidth, int screenHeight)
{
	for (int i = grid->dimension; i < screenWidth; i += grid->dimension)
	{
		DrawLine(0, i, screenWidth, i, WHITE);
		DrawLine(i, 0, i, screenHeight, WHITE);
	}
}