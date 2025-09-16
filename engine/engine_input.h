#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

void EngineInput_OnKeyDown(WPARAM key);
void EngineInput_OnKeyUp(WPARAM key);
BOOL EngineInput_IsKeyDown(int vk_code);

#endif 