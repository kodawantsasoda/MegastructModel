#include "SpatialGrid.h"

int32_t index1d(Grid* grid, float ordinate)
{
	return (int32_t)floor(ordinate / grid->spacing);
}
float position1dLow(Grid* grid, int32_t index)
{
	return (float)index * grid->spacing;
}
Vector2 index2d(Grid* grid, Vector2 pos)
{
	Vector2 translation = { index1d(grid, pos.x), index1d(grid, pos.y) };
	return translation;
}