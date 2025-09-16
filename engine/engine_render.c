#include <windows.h>
#include "resource.h"
#include "engine_render.h"

//³õÊ¼»¯»æÍ¼¾ä±ú
static HDC hdc = NULL;

void EngineRender_Init(HWND hWnd)
{
	//»ñÈ¡»æÍ¼¾ä±ú
	hdc = GetDC(hWnd);
}

void EngineRender_Release(HWND hWnd)
{
	ReleaseDC(hWnd, hdc);
	hdc = NULL;
}

void EngineRender_DrawRect(int x, int y, int w, int h, COLORREF color)
{
	if (!hdc)return;

	HBRUSH brush = CreateSolidBrush(color);
	RECT rc = { x,y,x + w,y + h };
	FillRect(hdc, &rc, brush);
	//ÊÍ·Å±ÊË¢
	DeleteObject(brush);
}