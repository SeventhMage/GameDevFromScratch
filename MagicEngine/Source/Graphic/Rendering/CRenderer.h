#ifndef _MAGIC_C_RENDER_H_
#define _MAGIC_C_RENDER_H_

#include <vector>
#include <map>
#include <string>

#include "Graphic/Rendering/IRenderer.h"

namespace Magic
{
    class CRenderer : public IRenderer
    {
    public:
        CRenderer(int width, int height);
        virtual void OnViewportChange() {}

        virtual void SetRenderTarget(IRenderTarget *) override;
        virtual void AddRenderInput(IRenderInput *) override;
        virtual void Resize(int width, int height) override;
        virtual void SetGlobalUniform(const char *name, const void *data, int size);
        virtual void Begin() override;
        virtual void Render() override;
        virtual void End() override;
    protected:
        IRenderTarget *_RenderTarget;
        std::vector<IRenderInput *> _RenderInputs;
        int _Width;
        int _Height;
        std::map<std::string, std::vector<float>> _GlobalUniforms;
    };
}

#endif