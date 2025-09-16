#include <windows.h>
#include "resource.h"
#include "engine_render.h"

//��ʼ����ͼ���
static HDC hdc = NULL;

void EngineRender_Init(HWND hWnd)
{
	//��ȡ��ͼ���
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
	//�ͷű�ˢ
	DeleteObject(brush);
}