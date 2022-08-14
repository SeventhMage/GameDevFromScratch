#include "Scene/CModel.h"
#include "Graphic/Rendering/CRenderInput.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    CModel::CModel(IMesh *mesh, IMaterial *material)
    :_Mesh(mesh), _Material(material), _RenderInput(NEW CRenderInput())
    {
    }
    CModel::~CModel()
    {
        SAFE_DELETE(_RenderInput);
    }
    void CModel::SubmitToRenderQueue(IRenderer *renderer)
    {
        renderer->AddRenderInput(_RenderInput);
    }
    void CModel::SetMesh(IMesh *mesh)
    {
        _Mesh = mesh;
    }
    void CModel::SetMaterial(IMaterial *material)
    {
        _Material = material;
    }

    void CModel::Update()
    {

    }

    void CModel::GenerateRenderInputData()
    {

    }

}