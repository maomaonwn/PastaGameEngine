#include <windows.h>
#include "engine_window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	EngineWindow_Init(hInstance, nCmdShow);

	//��Ϸ��ѭ��
	MSG msg;
	BOOL running = TRUE;
	while (running)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message = WM_QUIT)running = FALSE;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//������ʵ����ѭ���߼�
		
#pragma region ����ϵͳ�ĵ���
		//��ʱ���δ�
		EngineTimer_Tick();

		//��ȡ���ھ����Ĭ���������ڵľ����
		HWND hWnd = EngineWindow_GetHWND();

		//��Ⱦ��ʼ��
		EngineRender_Init(hWnd);
#pragma region ��Ⱦ����
		EngineRender_DrawRect(100, 100, 200, 150, RGB(255, 0, 0));
#pragma endregion
		//��Ⱦ����
		EngineRender_Release(hWnd);

#pragma endregion
	}
	return 0;
}