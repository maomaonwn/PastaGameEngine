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
	}
	return 0;
}