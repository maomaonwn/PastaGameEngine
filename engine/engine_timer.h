#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

#include <windows.h>
#include "resource.h"

void EngineTimer_Init();
void EngineTimer_Tick();
float EngineTimer_GetDeltaTime();
float EngineTimer_GetTime();

#endif 
