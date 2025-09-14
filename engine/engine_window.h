#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <windows.h>
#include "resource.h"

BOOL EngineWindow_Init(HINSTANCE hInstance, int nCmdShow);
HWND EngineWindow_GetHWND();

#endif
