#pragma once
#ifndef SPATIALGRID_H
#define SPATIALGRID_H

#include "entity.h"
#include "arena.h"

const int GRID_SIZE = 60;
const int MAX_ENTITIES_IN_CELL = 10;

typedef struct Cell
{
	int entityIndex;
	Cell* next;
} Cell;

typedef struct Grid
{
	Vector2 minBound;
	Vector2 maxBound;
	float dimension;
	float spacing;
	Cell* cells[GRID_SIZE];
	Arena arena;
	unsigned char backing_buffer[MAX_ENTITIES * sizeof(Cell)];
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
void NewClient(Entity* entity);
void Insert(Grid* grid, Entity* entity);

void DrawGrid(Grid* grid);

#endif
