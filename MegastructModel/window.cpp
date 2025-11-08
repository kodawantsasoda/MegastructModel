#include "window.h"

Window* WindowInit()
{
	Window* win = (Window*)malloc(sizeof(Window));
	return win;
}

void WindowFree(Window* win)
{
	free(win);
}

//initializing the window and preparing our virtual canvas to be drawn into
void WindowOpen(Window* win)
{
	//window initialization
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT, "SPACE INVADERS");
	SetWindowMinSize(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT);

	win->virtualCanvas = LoadRenderTexture(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT);
	//Preparing our virtual texture to be drawn onto
	SetTextureFilter(win->virtualCanvas.texture, TEXTURE_FILTER_POINT);
}

void DrawVirtualResolution(Window* win)
{
	Rectangle drawnVirtualRect =
	{
		(GetScreenWidth() - ((float)VIRTUAL_SCREEN_WIDTH * win->scale)) * 0.5f,
		(GetScreenHeight() - ((float)VIRTUAL_SCREEN_HEIGHT * win->scale)) * 0.5f,
		(float)VIRTUAL_SCREEN_WIDTH * win->scale,
		(float)VIRTUAL_SCREEN_HEIGHT * win->scale
	};

	Rectangle fullScreenRect = { 0, 0, GetScreenWidth(), GetScreenHeight() };

	DrawTexturePro(win->virtualCanvas.texture, VIRTUAL_RES_RECT, drawnVirtualRect, ZERO_POS, 0.0f, WHITE);
}

//determining 
void DetermineScale(Window* win)
{
	//for testing purposes only, adjust/delete if needed, just make sure to set window size whenever toggling to full screen mode
	if (GetKeyPressed() == KEY_F11)
	{
		ToggleFullscreen();
		if (IsWindowFullscreen())
		{
			SetWindowSize(1920, 1080);
		}
	}
	win->scale = MIN((float)GetScreenWidth() / VIRTUAL_SCREEN_WIDTH, (float)GetScreenHeight() / VIRTUAL_SCREEN_HEIGHT);
}

//calculating mouse position in relation to the virtual resolution with the actual resolution
void DetermineVirtualMouse(Window* win)
{
	win->mousePos = GetMousePosition();
	//offsetting the mouse to adjust for black bars on the side of screen in case of aspect ratio mismatch
	win->virtualMousePos.x = (win->mousePos.x - (GetScreenWidth() - (VIRTUAL_SCREEN_WIDTH * win->scale)) * 0.5f) / win->scale;
	win->virtualMousePos.y = (win->mousePos.y - (GetScreenHeight() - (VIRTUAL_SCREEN_HEIGHT * win->scale)) * 0.5f) / win->scale;
	win->virtualMousePos = Vector2Clamp(win->virtualMousePos, ZERO_POS, VIRTUAL_RES_BOUNDS);
}

void DrawCanvas(Window* win)
{
	DetermineScale(win);
	DetermineVirtualMouse(win);
}