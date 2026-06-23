#pragma once

#include <windows.h>

// Lifecycle
BOOL EngineRender_Init(HWND hWnd);
void EngineRender_Shutdown(void);

// Frame
void EngineRender_BeginFrame(void);
void EngineRender_EndFrame(void);

// Draw commands (all draw to back buffer, presented at EndFrame)
void EngineRender_Clear(COLORREF color);
void EngineRender_DrawRect(int x, int y, int w, int h, COLORREF color);
void EngineRender_DrawRectOutline(int x, int y, int w, int h, COLORREF color);
void EngineRender_DrawBitmap(HBITMAP hBitmap, int x, int y, int w, int h);
void EngineRender_DrawText(const char* text, int x, int y, COLORREF color);
