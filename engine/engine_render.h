#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

void EngineRender_Init(HWND hWnd);
void EngineRender_Release(HWND hWnd);
void EngineRender_DrawRect(int x, int y, int w, int h, COLORREF color);

#endif