#ifndef _MAGIC_S_WIN_RENDER_CONTEXT_H_
#define _MAGIC_S_WIN_RENDER_CONTEXT_H_

#include <Windows.h>

#include "Graphic/Rendering/IRenderContext.h"

namespace Magic
{
    struct SWinRenderContext : public IRenderContext
    {
        HWND hWnd;
        HDC hMemoryDC;
        HDC hWindowDC;
        HBITMAP hBitmap;
        BITMAPINFO bitmapInfo;
    };
}

#endif