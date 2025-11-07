#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

//To be used for determining scaling
#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

//dimensions for out virtual screen resolution. We chose this to play well with scaling to 1080p and 4k resolutions
const int VIRTUAL_SCREEN_WIDTH = 320;
const int VIRTUAL_SCREEN_HEIGHT = 180;

const Rectangle VIRTUAL_RES_RECT = { 0.0f, 0.0f, (float)VIRTUAL_SCREEN_WIDTH, (float)-VIRTUAL_SCREEN_HEIGHT };

//positions
const Vector2 VIRTUAL_RES_BOUNDS = { (float)VIRTUAL_SCREEN_WIDTH, (float)VIRTUAL_SCREEN_HEIGHT };
const Vector2 ZERO_POS{ 0,0 };

//typedef struct Window Window;

typedef struct Window 
{
	//this is the "canvas" we will be rendering to, and the initial design resolution for our application
	RenderTexture2D virtualCanvas;

	//scaling for determining size and position for textures
	float scale = 1.0f;

	Vector2 mousePos{ 0, 0 };
	Vector2 virtualMousePos{ 0, 0 };
}Window;

Window* WindowInit();
void WindowFree(Window* win);
void WindowOpen(Window* win);
void DrawVirtualResolution(Window* win);
void DetermineScale(Window* win);
void DetermineVirtualMouse(Window* win);
void DrawCanvas(Window* win);

#endif 