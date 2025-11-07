#include "game.h"

void Run()
{
	window = WindowInit();
	WindowOpen(window);

	Setup();


	while (!WindowShouldClose())
	{
		DrawCanvas(window);
		Update();
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