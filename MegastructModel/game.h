#pragma once
#ifndef GAME_H
#define GAME_H

#include "window.h"
#include "entity.h"
#include "SpatialGrid.h"

static Window* window;

typedef struct Game
{
	Grid grid;
} Game;

void Run();
void InitGame(Game* grid);

#endif