#include<windows.h>

_declspec(dllexport) void HackMessageError()
{
	MessageBox(NULL, "您的电脑已被劫持!", "Windows提示", MB_ICONERROR | MB_OK);
}