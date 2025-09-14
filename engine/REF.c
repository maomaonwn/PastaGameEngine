#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include "resource.h"

#define TIMER_ID1 1
#define TIMER_ID5 5

void Paint();
void PaintInit(HWND hWnd);
void DestroyTimer(HWND hWnd);

/// <summary>
/// 1.消息处理函数
/// </summary>
/// <param name="hWnd"></param>
/// <param name="msgId"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd,UINT msgId,WPARAM wParam,LPARAM lParam)
{
	HDC			hdc;
	char		buffer[80];
	static int	counter1 = 0, counter2 = 0;

	//根据消息Id处理不同的消息
	switch (msgId)
	{
		//销毁时产生的消息
		case WM_DESTROY:
			PostQuitMessage(0);	//发送WM_QUIT退出消息
			DestroyTimer(hWnd);	//销毁定时器
			break;
		//创建窗口时
		case WM_CREATE:
			//创建按钮
			CreateWindow("button", "push button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,100,100,100,100,hWnd,0,((LPCREATESTRUCT)lParam)->hInstance,NULL);
			//创建定时器
			SetTimer(hWnd, TIMER_ID1, 1000, NULL);
			SetTimer(hWnd, TIMER_ID5, 5000, NULL);
			break;
		case WM_TIMER:
			switch (wParam) 
			{
			case TIMER_ID1:
				hdc = GetDC(hWnd);
				sprintf(buffer, TEXT("执行的次数%d"), ++counter1);
				TextOut(hdc, 0, 0, buffer, strlen(buffer));
				ReleaseDC(hWnd, hdc);
				break;
			case TIMER_ID5:
				hdc = GetDC(hWnd);
				sprintf(buffer, TEXT("执行的次数%d"), ++counter2);
				TextOut(hdc, 0, 20, buffer, strlen(buffer));
				ReleaseDC(hWnd, hdc);
				break;
			}
			break;

		//子控件给父类发送消息 或 选择了菜单的某项时
		case WM_COMMAND:
			MessageBox(hWnd, TEXT("成功点击按钮！"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
			break;
		//绘图时
		case WM_PAINT:
			PaintInit(hWnd);
			break;
		//字符输入时
		//case WM_CHAR:
		//	switch (wParam)
		//	{
		//	//case 'A':
		//	//	break;
		//	//case 'a':
		//	//	break;
		//	//case VK_ESCAPE:
		//	//	break;
		//	}
		//	break;
	}

	//系统处理其他消息
	return DefWindowProc(hWnd, msgId, wParam, lParam);
}

void RegisterWndClass();
void RecycleMSG();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//2.注册窗口类
	RegisterWndClass(hInstance);

	//3.创建窗口
	HWND hWnd = CreateWindow(TEXT("Main"),	//窗口类名
		TEXT("MainWindow"),	//窗口标题
		WS_OVERLAPPEDWINDOW,	//窗口样式（窗口类样式是大样式）
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,	//窗口位置和大小
		NULL, NULL, hInstance, NULL);	//父窗口句柄，菜单句柄，实例句柄，附加参数

	//4.显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//5.消息循环
	RecycleMSG();	

	return 0;
}

/// <summary>
/// 注册窗口类
/// </summary>
/// <param name="hInstance">程序的实例句柄，系统访问WinMain时会自动分配一个</param>
void RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASS wndclass = { 0 };

	//窗口类的附加内存，相当于缓存区，通常为0
	wndclass.cbClsExtra = 0;
	//窗口的附加内存，相当于缓存区，通常为0
	wndclass.cbWndExtra = 0;
	//获取笔刷，设置背景色
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = NULL;	//鼠标指针样式
	wndclass.hIcon = NULL;		//系统图标
	wndclass.hInstance = hInstance;
	//消息处理函数地址
	wndclass.lpfnWndProc = WndProc;
	//类名
	wndclass.lpszClassName = TEXT("Main");
	wndclass.lpszMenuName = (char *)IDR_MENU1;	//菜单 NULL为不要菜单
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	//窗口样式

	//注册到系统中，写入系统内核中
	RegisterClass(&wndclass);
}

/// <summary>
/// 消息循环
/// </summary>
void RecycleMSG()
{
	MSG msg = { 0 };
	//抓取消息
	while (GetMessage(&msg, NULL, 0, 0))	//若指定了固定的窗口句柄则只会抓取该窗口消息，NULL则表示抓本进程的消息
	{
		//翻译消息
		TranslateMessage(&msg);
		//分发消息
		DispatchMessage(&msg);
	}
}

#pragma region GDI

/// <summary>
/// GDI绘图初始化
/// </summary>
/// <param name="hWnd"></param>
void PaintInit(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	//获取绘图句柄，或称获取画笔
	HDC hdc =BeginPaint(hWnd, &ps);	

	/*初始化笔刷*/
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	//将指定图形对象选入指定设备上下文中
	HGDIOBJ defaultBrush = SelectObject(hdc, hBrush);	//返回原来的笔刷

	Paint();	//GDI绘图

	//重设回默认笔刷
	SelectObject(hdc, defaultBrush);
	//释放笔刷
	DeleteObject(hBrush);
	//释放画笔
	EndPaint(hWnd, &ps);
}

/// <summary>
/// GDI绘图
/// </summary>
void Paint()
{

}
#pragma endregion

#pragma region Timer

/// <summary>
/// 销毁定时器
/// </summary>
/// <param name="hWnd"></param>
void DestroyTimer(HWND hWnd)
{
	KillTimer(hWnd, TIMER_ID1);
	KillTimer(hWnd, TIMER_ID5);
}

#pragma endregion
