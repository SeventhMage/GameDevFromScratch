#include "CRenderer.h"
#include <cstring>

namespace Magic
{
    CRenderer::CRenderer(int width, int height)
    :_RenderTarget(nullptr), _Width(width), _Height(height)
    {

    }

    void CRenderer::SetRenderTarget(IRenderTarget * renderTarget)
    {
        _RenderTarget = renderTarget;
    }
    void CRenderer::AddRenderInput(IRenderInput *renderInput)
    {
        _RenderInputs.push_back(renderInput);
    }

    void CRenderer::Resize(int width, int height)
    {
        _Width = width;
        _Height = height;
    }

    void CRenderer::SetGlobalUniform(const char *name, const void *data, int size)
    {
        std::vector<float> value(size);
        memcpy(value.data(), data, size);
        _GlobalUniforms[name] = value;
    }

    void CRenderer::Begin()
    {
        Clear();
    }

    void CRenderer::Render()
    {
        for (auto renderInput : _RenderInputs)
        {
            Draw(renderInput);
        }
    }

    void CRenderer::End()
    {
        _RenderInputs.clear();
    }
}