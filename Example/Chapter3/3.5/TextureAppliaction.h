#ifndef _MAGIC_RENDERER_APPLICATION_H_
#define _MAGIC_RENDERER_APPLICATION_H_

#include "Application/CApplication.h"
#include "Graphic/Rendering/CRenderInput.h"
#include "Graphic/Rendering/IShaderProgram.h"
#include "Graphic/Rendering/CGeometry.h"
#include "Foundation/Math/Matrix4x4.hpp"

namespace Magic
{
    class TextureApplication : public CApplication
    {
        DECLARE_INITIALIZE;
        DECLARE_TERMINATE;
    public:
        virtual bool OnInitialize() override;
        virtual bool OnTerminate() override;
        virtual void OnUpdate() override;

    private:
        CRenderInput _RenderInput_0;
        CRenderInput _RenderInput_1;
        CGeometry *_Geometry;
        IShaderProgram *_ShaderProgram_0;
        IShaderProgram *_ShaderProgram_1;
        ITexture *_Texture;
        Matrix4x4f _ViewMat;
        Matrix4x4f _ProjMat;
    };

    REGISTER_INITIALIZE(TextureApplication);
    REGISTER_TERMINATE(TextureApplication);

}

#endif