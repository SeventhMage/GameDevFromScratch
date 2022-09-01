#ifndef _MAGIC_RENDERER_APPLICATION_H_
#define _MAGIC_RENDERER_APPLICATION_H_

#include "Application/CApplication.h"
#include "Graphic/Rendering/CRenderInput.h"
#include "Graphic/Rendering/IShaderProgram.h"
#include "Graphic/Rendering/CGeometry.h"

namespace Magic
{
    class RendererApplication : public CApplication
    {
        DECLARE_INITIALIZE;
        DECLARE_TERMINATE;
    public:
        virtual bool OnInitialize() override;
        virtual bool OnTerminate() override;
        virtual void OnUpdate() override;

    private:
        CRenderInput _RenderInput;
        CGeometry *_Geometry;
        IShaderProgram *_ShaderProgram;
        ITexture *_Texture;
    };

    REGISTER_INITIALIZE(RendererApplication);
    REGISTER_TERMINATE(RendererApplication);

}

#endif