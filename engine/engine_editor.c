#include <windows.h>
#include "resource.h"
#include "engine_editor.h"

/// <summary>
/// �½���־����
/// </summary>
/// <param name="hWnd"></param>
/// <param name="hInstance"></param>
HWND CreateLogWindow(HWND hWnd, HINSTANCE hInstance)
{
	HWND hLogWindow = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT",		//�ؼ�����
		"",			//��ʼ����
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		10, 380, 500, 150,	//λ�úʹ�С
		hWnd,			//�����ھ��
		(HMENU)1001,	//�ؼ�ID
		hInstance,
		NULL);

	return hLogWindow;
}

/// <summary>
/// ����־����׷����־
/// </summary>
/// <param name="hLogWindow"></param>
/// <param name="text"></param>
void AppendLog(HWND hLogWindow, const char* text)
{
	//��ȡ��ǰ�ı�����
	int len = GetWindowTextLength(hLogWindow);
	//���ù��λ�õ��ı�ĩβ
	SendMessage(hLogWindow, EM_SETSEL, (WPARAM)len, (LPARAM)len);
	//�������ı�
	SendMessage(hLogWindow, EM_REPLACESEL, FALSE, (LPARAM)text);
	//���뻻�з�
	SendMessage(hLogWindow, EM_REPLACESEL, FALSE, (LPARAM)"\r\n");
}