#include <windows.h>
#include "resource.h"
#include "engine_game.h"
#include "user.h"

GameCallBack ENTER = NULL;
GameCallBack UPDATE = NULL;
GameCallBack EXIT = NULL;

void SetEnter(GameCallBack func) { ENTER = func; }
void SetUpdate(GameCallBack func) { UPDATE = func; }
void SetExit(GameCallBack func) { EXIT = func; }

void InitGameLifeCycle()
{
	SetEnter(OnEnter);
	SetUpdate(OnUpdate);
	SetExit(OnExit);
}
