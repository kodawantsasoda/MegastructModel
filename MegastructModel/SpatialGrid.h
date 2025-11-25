#pragma once
#ifndef SPATIALGRID_H
#define SPATIALGRID_H

#include <stdint.h>
#include <raylib.h>
#include <raymath.h>

typedef struct Grid
{
	Vector2 minBound;
	Vector2 maxBound;
	float dimension;
} Grid;

typedef struct SquareQuery
{
	Vector2 centerPos;
	float radius;
} SquareQuery;

void InitGrid(Grid* grid, Vector2 minBound, Vector2 maxBound, float dimension);
int GetIndex(Grid* grid, Vector2 pos);
float sat(float x);

//Grid functionality
int32_t index1d(Grid* grid, float ordinate);
float position1dLow(Grid* grid, int32_t index);
Vector2 index2d(Grid* grid, Vector2 pos);

//Query functionality
Vector2 firstCell(SquareQuery* square, Grid* grid);
Vector2 nextCell(SquareQuery* square, Vector2 cell, Grid* grid);
bool inRange(SquareQuery* square, Vector2 pos);

void DrawGrid(Grid* grid);

#endif
