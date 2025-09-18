#include <windows.h>
#include <stdio.h>

/// <summary>
/// ����һ������̨���ڱ�׼��������ĵ���
/// </summary>
void AttachConsoleForDebug()
{
	AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    printf("------------------------------------------------------\n");
	printf("| Console attached for standard library debug output |\n");
    printf("------------------------------------------------------\n\n");
}