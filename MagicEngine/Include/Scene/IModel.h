#ifndef _MAGIC_I_MODEL_H_
#define _MAGIC_I_MODEL_H_

#include "Foundation/Object/IComponent.h"
#include "Resource/IMesh.h"
#include "Resource/IMaterial.h"
#include "Graphic/Rendering/IRenderer.h"

namespace Magic
{
    class IModel : public IComponent
    {
    public:
        virtual ~IModel(){}
        virtual void SubmitToRenderQueue(IRenderer *) = 0;
        virtual void SetMesh(IMesh *) = 0;
        virtual void SetMaterial(IMaterial *) = 0;
        virtual void Update() = 0;
    };
}

#endif