#include "game.h"

void Run()
{
	window = WindowInit();
	WindowOpen(window);

	Grid grid;
	InitGrid(&grid, { 0, 0 }, { (float)GetScreenWidth(), (float)GetScreenHeight() }, 10.0f);
	Setup();

	SetTargetFPS(60);
	SetConfigFlags(FLAG_VSYNC_HINT);
	
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
		Insert(&grid, &gameState.allEntities[0]);
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
	UnloadRenderTexture(window->virtualCanvas);
	CloseWindow();

	WindowFree(window);
	window = NULL;
}