#include <windows.h>
#include "resource.h"
#include "engine_system.h"

static LARGE_INTEGER freq, last_tick, now_tick;
static float delta_time = 0.0f;
static float total_time = 0.0f;

void EngineTimer_Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&last_tick);
	total_time = 0.0f;
}

void EngineTimer_Tick()
{
	QueryPerformanceCounter(&now_tick);
	delta_time = (float)(now_tick.QuadPart - last_tick.QuadPart) / freq.QuadPart;
	total_time += delta_time;
	last_tick = now_tick;
}

float EngineTimer_GetDeltaTime() { return delta_time; }
float EngineTimer_GetTime() { return total_time; }