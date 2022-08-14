#ifndef _MAGIC_C_MODEL_H_
#define _MAGIC_C_MODEL_H_

#include <memory>

#include "IModel.h"
#include "Graphic/Rendering/IRenderInput.h"

namespace Magic
{
    class CModel : public IModel
    {
    public:
        CModel(IMesh *, IMaterial *);
        virtual ~CModel();
        virtual void SubmitToRenderQueue(IRenderer *);
        virtual void SetMesh(IMesh *);
        virtual void SetMaterial(IMaterial *);
        virtual void Update();
    private:
        void GenerateRenderInputData();
    private:
        IMesh *_Mesh;
        IMaterial *_Material;
        IRenderInput *_RenderInput;
    };
}

#endif