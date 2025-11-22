#include "game.h"

void Run()
{
	window = WindowInit();
	WindowOpen(window);

	Grid grid;
	grid.spacing = 20;

	Setup();

	SetTargetFPS(60);
	SetConfigFlags(FLAG_VSYNC_HINT);
	
	while (!WindowShouldClose())
	{
		Update();
		/*****************************************************
		VIRTUAL SCREEN DRAWING*/
		BeginTextureMode(window->virtualCanvas);
		ClearBackground(BLACK);
		DrawCanvas(window);

		//Draw stuff
		Draw();
		DrawGrid(&grid, GetScreenWidth(), GetScreenHeight());

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