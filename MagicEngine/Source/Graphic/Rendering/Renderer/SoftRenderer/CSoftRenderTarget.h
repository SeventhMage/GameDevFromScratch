#ifndef _MAGIC_C_SOFT_RENDER_TARGET_H_
#define _MAGIC_C_SOFT_RENDER_TARGET_H_

#include "Graphic/Rendering/IRenderTarget.h"

namespace Magic
{
    class CSoftRenderTarget : public IRenderTarget
    {
    public:
        CSoftRenderTarget(int width, int height);
        virtual ~CSoftRenderTarget();
        virtual int GetWidth() const { return _Width; }
        virtual int GetHeight() const { return _Height;}
        unsigned int *&GetColorBuffer() {return _ColorBuffer;}
        float *&GetDepthBuffer() {return _DepthBuffer;}
        unsigned int *&GetStencilBuffer() {return _StencilBuffer;}
    public:
        int _Width;
        int _Height;
        unsigned int *_ColorBuffer;
        float *_DepthBuffer;
        unsigned int *_StencilBuffer;
    };
}

#endif