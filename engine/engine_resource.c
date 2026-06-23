#include <windows.h>
#include "engine_resource.h"

HBITMAP EngineResource_LoadBitmap(const char* filename)
{
	return (HBITMAP)LoadImageA(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void EngineResource_FreeBitmap(HBITMAP hBitmap)
{
	if (hBitmap) DeleteObject(hBitmap);
}
