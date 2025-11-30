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
	float spacing;
} Grid;

typedef struct SquareQuery
{
	Vector2 centerPos;
	float radius;
} SquareQuery;

//TODO: put in math helper file
float sat(float x);

void InitGrid(Grid* grid, Vector2 minBound, Vector2 maxBound, float dimension);
int GetIndex(Grid* grid, Vector2 pos);
int GetIndexY(Grid* grid, Vector2 pos);

void DrawGrid(Grid* grid);

#endif
