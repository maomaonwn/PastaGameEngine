#include <windows.h>
#include "engine_system.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	EngineWindow_Init(hInstance, nCmdShow);
	AttachConsoleForDebug(); //分配用于标准输入输出调试的控制台
	InitGameLifeCycle();

	//ENTER生命周期
	if (ENTER)ENTER();

	//游戏主循环
	MSG msg;
	BOOL running = TRUE;
	while (running)
	{
		//主动轮询式消息循环
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)running = FALSE;

			//翻译消息
			TranslateMessage(&msg);
			//分发消息
			DispatchMessage(&msg);
		}

		//在这里实现主循环逻辑

#pragma region 基础系统的调用
		//定时器滴答
		EngineTimer_Tick();

		//获取窗口句柄（默认是主窗口的句柄）
		HWND hWnd = EngineWindow_GetHWND();

		//渲染初始化
		EngineRender_Init(hWnd);
#pragma region 渲染更新
		EngineRender_DrawRect(100, 100, 200, 150, RGB(255, 0, 0));
#pragma endregion
		//渲染结束
		EngineRender_Release(hWnd);
#pragma endregion

		//UPDATE生命周期
		if (UPDATE)UPDATE();
	}

	//EXIT生命周期
	if (EXIT)EXIT();
	return 0;
}