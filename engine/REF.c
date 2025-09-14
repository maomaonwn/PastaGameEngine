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
/// 1.��Ϣ������
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

	//������ϢId����ͬ����Ϣ
	switch (msgId)
	{
		//����ʱ��������Ϣ
		case WM_DESTROY:
			PostQuitMessage(0);	//����WM_QUIT�˳���Ϣ
			DestroyTimer(hWnd);	//���ٶ�ʱ��
			break;
		//��������ʱ
		case WM_CREATE:
			//������ť
			CreateWindow("button", "push button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,100,100,100,100,hWnd,0,((LPCREATESTRUCT)lParam)->hInstance,NULL);
			//������ʱ��
			SetTimer(hWnd, TIMER_ID1, 1000, NULL);
			SetTimer(hWnd, TIMER_ID5, 5000, NULL);
			break;
		case WM_TIMER:
			switch (wParam) 
			{
			case TIMER_ID1:
				hdc = GetDC(hWnd);
				sprintf(buffer, TEXT("ִ�еĴ���%d"), ++counter1);
				TextOut(hdc, 0, 0, buffer, strlen(buffer));
				ReleaseDC(hWnd, hdc);
				break;
			case TIMER_ID5:
				hdc = GetDC(hWnd);
				sprintf(buffer, TEXT("ִ�еĴ���%d"), ++counter2);
				TextOut(hdc, 0, 20, buffer, strlen(buffer));
				ReleaseDC(hWnd, hdc);
				break;
			}
			break;

		//�ӿؼ������෢����Ϣ �� ѡ���˲˵���ĳ��ʱ
		case WM_COMMAND:
			MessageBox(hWnd, TEXT("�ɹ������ť��"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
			break;
		//��ͼʱ
		case WM_PAINT:
			PaintInit(hWnd);
			break;
		//�ַ�����ʱ
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

	//ϵͳ����������Ϣ
	return DefWindowProc(hWnd, msgId, wParam, lParam);
}

void RegisterWndClass();
void RecycleMSG();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//2.ע�ᴰ����
	RegisterWndClass(hInstance);

	//3.��������
	HWND hWnd = CreateWindow(TEXT("Main"),	//��������
		TEXT("MainWindow"),	//���ڱ���
		WS_OVERLAPPEDWINDOW,	//������ʽ����������ʽ�Ǵ���ʽ��
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,	//����λ�úʹ�С
		NULL, NULL, hInstance, NULL);	//�����ھ�����˵������ʵ����������Ӳ���

	//4.��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//5.��Ϣѭ��
	RecycleMSG();	

	return 0;
}

/// <summary>
/// ע�ᴰ����
/// </summary>
/// <param name="hInstance">�����ʵ�������ϵͳ����WinMainʱ���Զ�����һ��</param>
void RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASS wndclass = { 0 };

	//������ĸ����ڴ棬�൱�ڻ�������ͨ��Ϊ0
	wndclass.cbClsExtra = 0;
	//���ڵĸ����ڴ棬�൱�ڻ�������ͨ��Ϊ0
	wndclass.cbWndExtra = 0;
	//��ȡ��ˢ�����ñ���ɫ
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = NULL;	//���ָ����ʽ
	wndclass.hIcon = NULL;		//ϵͳͼ��
	wndclass.hInstance = hInstance;
	//��Ϣ��������ַ
	wndclass.lpfnWndProc = WndProc;
	//����
	wndclass.lpszClassName = TEXT("Main");
	wndclass.lpszMenuName = (char *)IDR_MENU1;	//�˵� NULLΪ��Ҫ�˵�
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	//������ʽ

	//ע�ᵽϵͳ�У�д��ϵͳ�ں���
	RegisterClass(&wndclass);
}

/// <summary>
/// ��Ϣѭ��
/// </summary>
void RecycleMSG()
{
	MSG msg = { 0 };
	//ץȡ��Ϣ
	while (GetMessage(&msg, NULL, 0, 0))	//��ָ���˹̶��Ĵ��ھ����ֻ��ץȡ�ô�����Ϣ��NULL���ʾץ�����̵���Ϣ
	{
		//������Ϣ
		TranslateMessage(&msg);
		//�ַ���Ϣ
		DispatchMessage(&msg);
	}
}

#pragma region GDI

/// <summary>
/// GDI��ͼ��ʼ��
/// </summary>
/// <param name="hWnd"></param>
void PaintInit(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	//��ȡ��ͼ�������ƻ�ȡ����
	HDC hdc =BeginPaint(hWnd, &ps);	

	/*��ʼ����ˢ*/
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	//��ָ��ͼ�ζ���ѡ��ָ���豸��������
	HGDIOBJ defaultBrush = SelectObject(hdc, hBrush);	//����ԭ���ı�ˢ

	Paint();	//GDI��ͼ

	//�����Ĭ�ϱ�ˢ
	SelectObject(hdc, defaultBrush);
	//�ͷű�ˢ
	DeleteObject(hBrush);
	//�ͷŻ���
	EndPaint(hWnd, &ps);
}

/// <summary>
/// GDI��ͼ
/// </summary>
void Paint()
{

}
#pragma endregion

#pragma region Timer

/// <summary>
/// ���ٶ�ʱ��
/// </summary>
/// <param name="hWnd"></param>
void DestroyTimer(HWND hWnd)
{
	KillTimer(hWnd, TIMER_ID1);
	KillTimer(hWnd, TIMER_ID5);
}

#pragma endregion
