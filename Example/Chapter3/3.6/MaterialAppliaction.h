#ifndef _MAGIC_RENDERER_APPLICATION_H_
#define _MAGIC_RENDERER_APPLICATION_H_

#include "Application/CApplication.h"
#include "Graphic/Rendering/CRenderInput.h"
#include "Graphic/Rendering/IShaderProgram.h"
#include "Graphic/Rendering/CGeometry.h"
#include "Foundation/Math/Matrix4x4.hpp"
#include "Resource/IMaterial.h"
#include "Resource/IMesh.h"

#include <vector>
using namespace std;

namespace Magic
{
    class MaterialApplication : public CApplication
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
        IMaterial *_Material;
        IMesh *_Mesh;
        IShaderProgram *_ShaderProgram;
        vector<ITexture *> _Textures;
        Matrix4x4f _ViewMat;
        Matrix4x4f _ProjMat;
    };

    REGISTER_INITIALIZE(MaterialApplication);
    REGISTER_TERMINATE(MaterialApplication);

}

#endif