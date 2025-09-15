#include "engine_input.h"

static BOOL key_states[256] = { 0 };

void EngineInput_OnKeyDown(WPARAM key)
{
	if (key < 256)key_states[key] = TRUE;
}

void EngineInput_OnKeyUp(WPARAM key)
{
	if (key < 256)key_states[key] = FALSE;
}

BOOL EngineInput_IsKeyDown(int vk_code)
{
	return key_states[vk_code] ? TRUE : FALSE;
}