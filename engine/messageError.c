#include<windows.h>

_declspec(dllexport) void HackMessageError()
{
	MessageBox(NULL, "���ĵ����ѱ��ٳ�!", "Windows��ʾ", MB_ICONERROR | MB_OK);
}