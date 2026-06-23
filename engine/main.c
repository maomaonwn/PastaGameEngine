#include <windows.h>
#include "engine_system.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	EngineWindow_Init(hInstance, nCmdShow);
	AttachConsoleForDebug();
	InitGameLifeCycle();
	EngineTimer_Init();

	HWND hWnd = EngineMainWindow_GetHWND();
	EngineRender_Init(hWnd);

	if (ENTER) ENTER();

	MSG msg;
	BOOL running = TRUE;
	while (running)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) running = FALSE;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		EngineTimer_Tick();

		EngineRender_BeginFrame();
		if (UPDATE) UPDATE();
		EngineRender_EndFrame();
	}

	if (EXIT) EXIT();
	EngineRender_Shutdown();
	return 0;
}
