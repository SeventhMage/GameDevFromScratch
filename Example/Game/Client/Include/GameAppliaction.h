#ifndef _MAGIC_RENDERER_APPLICATION_H_
#define _MAGIC_RENDERER_APPLICATION_H_

#include "Application/CApplication.h"
#include "Graphic/Rendering/CRenderInput.h"
#include "Graphic/Rendering/IShaderProgram.h"
#include "Graphic/Rendering/CGeometry.h"
#include "Foundation/Math/Matrix4x4.hpp"

namespace Magic
{
    class GameApplication : public CApplication
    {
        DECLARE_INITIALIZE;
        DECLARE_TERMINATE;
    public:
        virtual bool OnInitialize() override;
        virtual bool OnTerminate() override;
        virtual void OnUpdate() override;
    private:
    };

    REGISTER_INITIALIZE(GameApplication);
    REGISTER_TERMINATE(GameApplication);

}

#endif