#pragma once

#include <windows.h>

#ifdef _cplusplus
extern "C" {
#endif

// Debug
typedef enum {
	LOGWARN,
	LOGERROR,
	LOGINFO
} ExType;

void DebugLog(const char* msg);
void DebugLogEx(ExType type, const char* fmt, ...);

// Render
void EngineRender_Clear(COLORREF color);
void EngineRender_DrawRect(int x, int y, int w, int h, COLORREF color);
void EngineRender_DrawRectOutline(int x, int y, int w, int h, COLORREF color);
void EngineRender_DrawBitmap(HBITMAP hBitmap, int x, int y, int w, int h);
void EngineRender_DrawText(const char* text, int x, int y, COLORREF color);

// Resource
HBITMAP EngineResource_LoadBitmap(const char* filename);
void EngineResource_FreeBitmap(HBITMAP hBitmap);

// Timer
float EngineTimer_GetDeltaTime(void);
float EngineTimer_GetTime(void);

// Input
BOOL EngineInput_IsKeyDown(int vk_code);

#ifdef _cplusplus
}
#endif
