#include "CSoftRenderTarget.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    CSoftRenderTarget::CSoftRenderTarget(int width, int height)
    :_Width(width), _Height(height), _ColorBuffer(NEW unsigned int[width * height]), _DepthBuffer(NEW float[width * height]), _StencilBuffer(NEW unsigned int[width * height])
    {

    }

    CSoftRenderTarget::~CSoftRenderTarget()
    {
        SAFE_DELETE_ARRAY(_ColorBuffer);
        SAFE_DELETE_ARRAY(_DepthBuffer);
        SAFE_DELETE_ARRAY(_StencilBuffer);
    }
}