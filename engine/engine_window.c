#include <windows.h>
#include "resource.h"
#include "engine_window.h"
#include "engine_editor.h"

static HWND hWnd = NULL;

LRESULT CALLBACK EngineWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/// <summary>
/// ���ڳ�ʼ��
/// </summary>
/// <param name="hInstance">�����ʵ�������ϵͳ����WinMainʱ���Զ�����һ��</param>
/// <param name="cCmdShow"></param>
/// <returns></returns>
BOOL EngineWindow_Init(HINSTANCE hInstance, int nCmdShow)
{
	//��ʼ��������
	WNDCLASS wc = { 0 };

#pragma region ���ô���������
	//������ĸ������ݣ��൱�ڻ�������ͨ��Ϊ0
	wc.cbClsExtra = 0;
	//���ڵĸ����ڴ棬�൱�ڻ�������ͨ��Ϊ0
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = EngineWndProc;
	wc.hInstance = hInstance;
	//����
	wc.lpszClassName = TEXT("Main");
	wc.lpszMenuName = (char*)IDR_MENU1;	//�˵� NULLΪ��Ҫ�˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;	//������ʽ
	//��ȡ��ˢ�����ñ���ɫ
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = NULL;	//���ָ����ʽ
	wc.hIcon = NULL;	//ϵͳͼ��;
#pragma endregion

	//ע�ᴰ���ൽϵͳ�У�д��ϵͳ�ں���
	RegisterClass(&wc);

#pragma region ��������������
	//��ȡ�����ڵĴ��ھ��
	hWnd = CreateWindow(TEXT("Main"), "Pasta Game Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	if (!hWnd) {
		MessageBox(NULL, "���ڴ���ʧ��!", "����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//����������
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

#pragma endregion

#pragma region ������������

	HWND hLogWindow = CreateLogWindow(hWnd, hInstance);
	ShowWindow(hLogWindow, nCmdShow);
	UpdateWindow(hLogWindow);

	return TRUE;

#pragma endregion
}

/// <summary>
/// ��ȡ�����ڵĴ��ھ��
/// </summary>
/// <returns></returns>
HWND EngineMainWindow_GetHWND()
{
	return hWnd;
}

/// <summary>
/// ������Ϣ�ص�����
/// </summary>
/// <remarks>����������ַ�������Ϣ���������</remarks>
/// <param name="hWnd"></param>
/// <param name="msg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK EngineWndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
	//������ϢId����ͬ����Ϣ
	switch (msgId)
	{
		//����ʱ��������Ϣ
		case WM_DESTROY:
			PostQuitMessage(0);	//����WM_QUIT�˳���Ϣ
			break;
	}

	//ϵͳ����������Ϣ
	return DefWindowProc(hWnd, msgId, wParam, lParam);
}