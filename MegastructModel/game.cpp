#include "game.h"

void Run()
{
	window = WindowInit();
	WindowOpen(window);

	Grid grid;
	InitGrid(&grid, { 0, 0 }, { 100, 100 }, 10.0f);

	Setup();

	SetTargetFPS(60);
	SetConfigFlags(FLAG_VSYNC_HINT);
	
	while (!WindowShouldClose())
	{
		Update();
		int x = GetIndex(&grid, { 56,0 });
		/*****************************************************
		VIRTUAL SCREEN DRAWING*/
		BeginTextureMode(window->virtualCanvas);
		ClearBackground(BLACK);
		DrawCanvas(window);

		//Draw stuff
		Draw();
		DrawGrid(&grid);

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