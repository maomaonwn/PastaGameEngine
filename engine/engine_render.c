#include <windows.h>
#include <string.h>
#include "engine_render.h"

/*
 * ======================== 双缓冲渲染架构 ========================
 *
 * 问题：如果每帧直接往屏幕(前缓冲区)上画，用户会看到"画了一半"的中间状态，
 *       表现为画面闪烁(flicker)。
 *
 * 解决：在内存中开辟一块和窗口等大的"后缓冲区"(back buffer)，
 *       所有绘制操作都画到后缓冲区上（用户看不见这个过程）。
 *       一帧画完后，用 BitBlt 一次性把后缓冲区的完整画面拷贝到屏幕。
 *       因为拷贝是瞬间完成的，用户永远只看到完整的帧，不会看到中间状态。
 *
 * 每帧数据流：
 *   BeginFrame()  ->  清空后缓冲区（此时屏幕仍显示上一帧）
 *   DrawXxx()     ->  所有绘制命令写入后缓冲区
 *   EndFrame()    ->  BitBlt(后缓冲区 -> 前缓冲区/屏幕)
 *
 * Win32 实现映射：
 *   前缓冲区 = GetDC(hWnd) 获得的 HDC，直连窗口显示像素
 *   后缓冲区 = CreateCompatibleDC + CreateCompatibleBitmap 创建的内存 DC
 * ================================================================
 */

/* 前缓冲区：直接关联窗口，写入即显示到屏幕 */
static HDC   s_hdcFront = NULL;
/* 后缓冲区 DC：内存中的画布，所有绘制先画到这里 */
static HDC   s_hdcBack = NULL;
/* 后缓冲区的位图对象（实际的像素存储区域，存在于 RAM 中） */
static HBITMAP s_hBackBuf = NULL;
/* 创建后缓冲区 DC 时被替换出来的默认位图，Shutdown 时需要还原回去以避免 GDI 泄漏 */
static HBITMAP s_hOldBmp = NULL;

static HWND  s_hWnd = NULL;
static int   s_width = 0;
static int   s_height = 0;

/*
 * 初始化渲染系统（程序启动时调用一次）
 * 创建一个与窗口客户区等大的后缓冲区
 */
BOOL EngineRender_Init(HWND hWnd)
{
	RECT rc;
	s_hWnd = hWnd;
	GetClientRect(hWnd, &rc);
	s_width = rc.right - rc.left;
	s_height = rc.bottom - rc.top;

	/* 获取窗口的设备上下文（前缓冲区） */
	s_hdcFront = GetDC(hWnd);

	/* 创建与前缓冲区兼容的内存 DC（后缓冲区的"画笔持有者"） */
	s_hdcBack = CreateCompatibleDC(s_hdcFront);

	/* 创建与窗口等大的位图（后缓冲区的实际像素存储） */
	s_hBackBuf = CreateCompatibleBitmap(s_hdcFront, s_width, s_height);

	/* 将位图选入后缓冲区 DC，此后对 s_hdcBack 的所有绘制都写入这块位图 */
	s_hOldBmp = (HBITMAP)SelectObject(s_hdcBack, s_hBackBuf);

	return TRUE;
}

/*
 * 销毁渲染系统（程序退出时调用一次）
 * 还原 DC 的默认位图，再释放所有 GDI 资源
 */
void EngineRender_Shutdown(void)
{
	if (s_hdcBack)
	{
		/* 先还原默认位图，才能安全删除我们创建的位图 */
		SelectObject(s_hdcBack, s_hOldBmp);
		DeleteObject(s_hBackBuf);
		DeleteDC(s_hdcBack);
	}
	if (s_hdcFront && s_hWnd)
	{
		ReleaseDC(s_hWnd, s_hdcFront);
	}
	s_hdcBack = NULL;
	s_hdcFront = NULL;
	s_hBackBuf = NULL;
	s_hWnd = NULL;
}

/*
 * 帧开始：用黑色清空后缓冲区，为本帧绘制做准备
 * 此时屏幕上仍然显示着上一帧的完整画面
 */
void EngineRender_BeginFrame(void)
{
	EngineRender_Clear(RGB(0, 0, 0));
}

/*
 * 帧结束：将后缓冲区的完整画面一次性拷贝到前缓冲区（屏幕）
 * BitBlt 是像素级内存拷贝（通常有显卡加速），速度极快，不会产生闪烁
 */
void EngineRender_EndFrame(void)
{
	BitBlt(s_hdcFront, 0, 0, s_width, s_height, s_hdcBack, 0, 0, SRCCOPY);
}

/* ======================== 绘制命令 ========================
 * 以下所有函数都画到后缓冲区(s_hdcBack)，不直接触碰屏幕。
 * 用户在 OnUpdate() 中调用这些函数，引擎在 EndFrame() 统一呈现。
 * ========================================================= */

/* 用指定颜色填充整个后缓冲区 */
void EngineRender_Clear(COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	RECT rc = { 0, 0, s_width, s_height };
	FillRect(s_hdcBack, &rc, brush);
	DeleteObject(brush);
}

/* 绘制一个填充矩形 */
void EngineRender_DrawRect(int x, int y, int w, int h, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	RECT rc = { x, y, x + w, y + h };
	FillRect(s_hdcBack, &rc, brush);
	DeleteObject(brush);
}

/* 绘制矩形边框（不填充内部），使用空画刷 + 实线画笔 */
void EngineRender_DrawRectOutline(int x, int y, int w, int h, COLORREF color)
{
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)SelectObject(s_hdcBack, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(s_hdcBack, GetStockObject(NULL_BRUSH));

	Rectangle(s_hdcBack, x, y, x + w, y + h);

	SelectObject(s_hdcBack, oldBrush);
	SelectObject(s_hdcBack, oldPen);
	DeleteObject(pen);
}

/*
 * 绘制位图（精灵）到后缓冲区
 * 原理：为源位图创建一个临时内存 DC，再用 StretchBlt 缩放拷贝到后缓冲区
 */
void EngineRender_DrawBitmap(HBITMAP hBitmap, int x, int y, int w, int h)
{
	if (!hBitmap) return;

	/* 为源位图创建临时 DC */
	HDC hdcMem = CreateCompatibleDC(s_hdcBack);
	HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hBitmap);

	/* 获取位图原始尺寸，作为 StretchBlt 的源矩形 */
	BITMAP bm;
	GetObject(hBitmap, sizeof(BITMAP), &bm);

	/* 从源 DC 缩放拷贝到后缓冲区 */
	StretchBlt(s_hdcBack, x, y, w, h, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	SelectObject(hdcMem, oldBmp);
	DeleteDC(hdcMem);
}

/* 绘制文字，背景透明不遮盖已有内容 */
void EngineRender_DrawText(const char* text, int x, int y, COLORREF color)
{
	if (!text) return;

	/* TRANSPARENT 模式：文字背景透明 */
	SetBkMode(s_hdcBack, TRANSPARENT);
	SetTextColor(s_hdcBack, color);
	TextOutA(s_hdcBack, x, y, text, (int)strlen(text));
}
