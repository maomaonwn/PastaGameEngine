#include <windows.h>
#include "resource.h"
#include "engine_editor.h"

/// <summary>
/// 新建日志窗口
/// </summary>
/// <param name="hWnd"></param>
/// <param name="hInstance"></param>
HWND CreateLogWindow(HWND hWnd, HINSTANCE hInstance)
{
	HWND hLogWindow = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT",		//控件类型
		"",			//初始内容
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		10, 380, 500, 150,	//位置和大小
		hWnd,			//父窗口句柄
		(HMENU)1001,	//控件ID
		hInstance,
		NULL);

	return hLogWindow;
}

/// <summary>
/// 在日志窗口追加日志
/// </summary>
/// <param name="hLogWindow"></param>
/// <param name="text"></param>
void AppendLog(HWND hLogWindow, const char* text)
{
	//获取当前文本长度
	int len = GetWindowTextLength(hLogWindow);
	//设置光标位置到文本末尾
	SendMessage(hLogWindow, EM_SETSEL, (WPARAM)len, (LPARAM)len);
	//插入新文本
	SendMessage(hLogWindow, EM_REPLACESEL, FALSE, (LPARAM)text);
	//插入换行符
	SendMessage(hLogWindow, EM_REPLACESEL, FALSE, (LPARAM)"\r\n");
}