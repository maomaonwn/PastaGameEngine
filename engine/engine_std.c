#include <windows.h>
#include <stdio.h>

/// <summary>
/// 分配一个控制台用于标准输入输出的调试
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