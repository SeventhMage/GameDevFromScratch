#ifdef _WIN32
#include "SWinRenderContext.h"
#include "Graphic/Rendering/Renderer/SoftRenderer/CSoftRenderer.h"
#include "Graphic/Rendering/Renderer/SoftRenderer/CSoftRenderTarget.h"

namespace Magic
{
    void CSoftRenderer::InitDriver(IRenderContext *context)
    {
        _RenderContext = context;

        SWinRenderContext *winContext = (SWinRenderContext *)_RenderContext;

        winContext->hWindowDC = GetDC(winContext->hWnd);
        winContext->hMemoryDC = CreateCompatibleDC(winContext->hWindowDC);

        memset(&winContext->bitmapInfo, 0, sizeof(BITMAPINFO));
        winContext->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        winContext->bitmapInfo.bmiHeader.biWidth = _Width;
        winContext->bitmapInfo.bmiHeader.biHeight = -_Height;
        winContext->bitmapInfo.bmiHeader.biPlanes = 1;
        winContext->bitmapInfo.bmiHeader.biBitCount = 32;
        winContext->bitmapInfo.bmiHeader.biCompression = BI_RGB;
    
        unsigned int *&colorBuffer = _FinalRenderTarget->GetColorBuffer();
        winContext->hBitmap = CreateDIBSection(winContext->hMemoryDC, &winContext->bitmapInfo, DIB_RGB_COLORS, (void **)&colorBuffer, 0, 0);

        SelectObject(winContext->hMemoryDC, winContext->hBitmap);
    }

    void CSoftRenderer::CleanDriver()
    {
        SWinRenderContext *winContext = (SWinRenderContext *)_RenderContext;
        DeleteObject(winContext->hBitmap);
        DeleteDC(winContext->hMemoryDC);
        ReleaseDC(winContext->hWnd, winContext->hWindowDC);
    }

    void CSoftRenderer::OnViewportChange()
    {
        SWinRenderContext *winContext = (SWinRenderContext *)_RenderContext;

        DeleteObject(winContext->hBitmap);

        winContext->bitmapInfo.bmiHeader.biWidth = _Width;
        winContext->bitmapInfo.bmiHeader.biHeight = -_Height;

        unsigned int *colorBuffer = _FinalRenderTarget->GetColorBuffer();
        winContext->hBitmap = CreateDIBSection(winContext->hMemoryDC, &winContext->bitmapInfo, DIB_RGB_COLORS, (void **)&colorBuffer, 0, 0);

        SelectObject(winContext->hMemoryDC, winContext->hBitmap);
    }

    void CSoftRenderer::DrawBuffer()
    {
        SWinRenderContext *winContext = (SWinRenderContext *)_RenderContext;
        BitBlt(winContext->hWindowDC, 0, 0, _Width, _Height, winContext->hMemoryDC, 0, 0, SRCCOPY);
    }
}

#endif