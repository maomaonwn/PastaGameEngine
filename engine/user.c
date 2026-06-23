#include "user.h"
#include "engine_api.h"

/**************在此自定义添加C语言标准库头文件**************/
#include <stdio.h>
/***********************************************************/

void OnEnter()
{
	DebugLog("Game started.");
}

void OnUpdate()
{
	EngineRender_DrawRect(50, 50, 200, 120, RGB(30, 120, 200));
	EngineRender_DrawRectOutline(50, 50, 200, 120, RGB(255, 255, 255));
	EngineRender_DrawText("PastaEngine Running", 60, 80, RGB(255, 255, 255));
}

void OnExit()
{

}
