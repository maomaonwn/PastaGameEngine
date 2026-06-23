#pragma once

#include <windows.h>

HBITMAP EngineResource_LoadBitmap(const char* filename);
void EngineResource_FreeBitmap(HBITMAP hBitmap);
