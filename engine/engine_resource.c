#include <windows.h>
#include "resource.h"
#include "engine_resource.h"

void EngineResource_LoadBitmap(const char* filename)
{
	return (void*)LoadImageA(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}