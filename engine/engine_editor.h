#pragma once

HWND CreateLogWindow(HWND hWnd, HINSTANCE hInstance);
void AppendLog(HWND hLogWindow, const char* text);