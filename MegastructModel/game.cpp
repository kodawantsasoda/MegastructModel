#include "game.h"

void Run()
{
	window = WindowInit();
	WindowOpen(window);

	while (!WindowShouldClose())
	{
		DrawCanvas(window);
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