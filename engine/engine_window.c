#include <windows.h>
#include "resource.h"
#include "engine_window.h"

static HWND hWnd = NULL;

LRESULT CALLBACK EngineWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/// <summary>
/// 窗口初始化
/// </summary>
/// <param name="hInstance">程序的实例句柄，系统访问WinMain时会自动分配一个</param>
/// <param name="cCmdShow"></param>
/// <returns></returns>
BOOL EngineWindow_Init(HINSTANCE hInstance, int nCmdShow)
{
	//初始化窗口类
	WNDCLASS wc = { 0 };

#pragma region 设置窗口类属性
	//窗口类的附加内容，相当于缓存区，通常为0
	wc.cbClsExtra = 0;
	//窗口的附加内存，相当于缓存区，通常为0
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = EngineWndProc;
	wc.hInstance = hInstance;
	//类名
	wc.lpszClassName = TEXT("Main");
	wc.lpszMenuName = (char*)IDR_MENU1;	//菜单 NULL为不要菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;	//窗口样式
	//获取笔刷，设置背景色
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = NULL;	//鼠标指针样式
	wc.hIcon = NULL;	//系统图标;
#pragma endregion

	//注册窗口类到系统中，写入系统内核中
	RegisterClass(&wc);

#pragma region 生成引擎主窗口
	//获取主窗口的窗口句柄
	hWnd = CreateWindow(TEXT("Main"), "Pasta Game Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	if (!hWnd)return FALSE;

	//生成主窗口
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
#pragma endregion
}

/// <summary>
/// 获取窗口的窗口句柄
/// </summary>
/// <returns></returns>
HWND EngineWindow_GetHWND()
{
	return hWnd;
}

/// <summary>
/// 窗口消息回调函数
/// </summary>
/// <remarks>可以在这里分发各类消息到其他板块</remarks>
/// <param name="hWnd"></param>
/// <param name="msg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK EngineWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}