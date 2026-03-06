#include "game.h"

void DebugSpatial(Entity* entity, Grid* grid)
{
	UpdateClient(grid, entity);
	int cell = 0;

	for (int i = 0; i < MAX_ENTITY_CELL_SIZE; i++)
	{
		cell = entity->cells[i];
		//TODO:: will have to adjust this... we get data loss going from float to int
		// i need to get rows and columns again.... got to figure out something more efficient for drawing... but might not be a way unfortunately.... so just add what you have already
		DrawRectangle((cell % (int)grid->dimension) * (int)grid->spacing, (cell / (int)grid->dimension) * (int)grid->spacing, (int)grid->spacing, (int)grid->spacing, YELLOW);
		
		if (cell == entity->cellMax)
		{
			break;
		}
	}
}

void Run()
{
	window = WindowInit();
	WindowOpen(window);

	Grid grid;
	InitGrid(&grid, { 0, 0 }, { (float)GetScreenWidth(), (float)GetScreenHeight() }, 10.0f);
	Setup();

	SetTargetFPS(60);
	SetConfigFlags(FLAG_VSYNC_HINT);

	Insert(&grid, &gameState.allEntities[0]);
	
	while (!WindowShouldClose())
	{
		Update();
		int x = GetIndex(&grid, { 0, 170 });
		//int y = GetIndexY(&grid, { 12, 30 });
		//where pos.x = width = column #; and pos.y = height = row #
		Vector2 pos = { (x % (int)grid.dimension) * grid.spacing, int(x / grid.dimension) * grid.spacing};
		Rectangle rec = { pos.x, pos.y, grid.spacing, grid.spacing };
		/*****************************************************
		VIRTUAL SCREEN DRAWING*/
		BeginTextureMode(window->virtualCanvas);
		ClearBackground(BLACK);
		DrawCanvas(window);

		//Draw stuff
		Draw();
		DrawGrid(&grid);

		DebugSpatial(&gameState.allEntities[0], &grid);

		//DrawRectangle(x * grid.spacing, 0, grid.spacing, grid.spacing, WHITE);
		DrawRectanglePro(rec, {0,0}, 1.0f, RED);

		EndTextureMode();
		/*****************************************************
		DRAWING VIRTUAL CANVAS ONTO CURRENT SCREEN RESOLUTION*/
		BeginDrawing();
		ClearBackground(WHITE);
		DrawVirtualResolution(window);
		EndDrawing();
		/*END DRAWING
		*****************************************************/
	}

	arenaFree(&grid.arena);
	UnloadRenderTexture(window->virtualCanvas);
	CloseWindow();

	WindowFree(window);
	window = NULL;
}