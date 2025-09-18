#include <windows.h>
#include "engine_system.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	EngineWindow_Init(hInstance, nCmdShow);
	AttachConsoleForDebug(); //�������ڱ�׼����������ԵĿ���̨
	InitGameLifeCycle();

	//ENTER��������
	if (ENTER)ENTER();

	//��Ϸ��ѭ��
	MSG msg;
	BOOL running = TRUE;
	while (running)
	{
		//������ѯʽ��Ϣѭ��
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)running = FALSE;

			//������Ϣ
			TranslateMessage(&msg);
			//�ַ���Ϣ
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

		//UPDATE��������
		if (UPDATE)UPDATE();
	}

	//EXIT��������
	if (EXIT)EXIT();
	return 0;
}