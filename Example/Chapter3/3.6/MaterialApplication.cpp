#include <iostream>
#include <fstream>
#include "MaterialAppliaction.h"
#include "ShaderProgram.hpp"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Math.hpp"
#include "Resource/CResourceMgr.h"


namespace Magic
{
    IMPLEMENT_APP_INITIALIZE(MaterialApplication);
    IMPLEMENT_APP_TERMINATE(MaterialApplication);

    bool MaterialApplication::OnInitialize()
    { 
        cout << "MaterialApplication::OnInitialize" << endl;

        _Mesh = (IMesh *)CResourceMgr::Instance()->LoadResource("cube.mesh");
        auto vertexCount = _Mesh->GetVertexCount();

        IVertexBuffer *vertexBuffer = Renderer->CreateVertexBuffer(vertexCount * (sizeof(Vector3f) + sizeof(Vector2f)), vertexCount);
        vertexBuffer->BufferData(_Mesh->GetVertices(), vertexCount * sizeof(Vector3f));
        vertexBuffer->BufferData(_Mesh->GetUVs(), vertexCount * sizeof(Vector2f), vertexCount * sizeof(Vector3f));
        vertexBuffer->GetAttribute()->SetPositionAttr(0, sizeof(Vector3f));
        vertexBuffer->GetAttribute()->SetUVAttr(sizeof(Vector3f) * vertexCount, sizeof(Vector2f));

        auto indexCount = _Mesh->GetIndexCount();
        IIndexBuffer *indexBuffer = Renderer->CreateIndexBuffer(indexCount * sizeof(int), indexCount);
        indexBuffer->BufferData(_Mesh->GetIndices());

        _Geometry = NEW CGeometry(vertexBuffer, indexBuffer);

        _Material = (IMaterial *)CResourceMgr::Instance()->LoadResource("wood.mat");

        assert(_Material);

        _ShaderProgram = Renderer->CreateShaderProgram(_Material->GetVertShader(), _Material->GetFragShader());
        int texQuantiity = _Material->GetTextureQuantity();
        for (int i = 0; i < texQuantiity; ++i)
        {
            auto texture = Renderer->CreateTexture(_Material->GetTexture(i));
            _Textures.push_back(texture);
            _RenderInput.SetTexture(0, texture);
        }

        _RenderInput.SetGeometry(_Geometry); 
        _RenderInput.SetShaderProgram(_ShaderProgram);


        Renderer->SetClearColor(0, 0, 0); 
        _ViewMat.BuildCameraLookAtMatrix(Vector3f(0, 0, 5.f), Vector3f(0, 0, -1), Vector3f(0, 1, 0));
        _ProjMat.BuildProjectionMatrixPerspectiveFovRH(PI / 3.f,   1.0f * GetWindowWidth() / GetWindowHeight(), 1.0f, 100.f);
        //_ProjMat.BuildProjectionMatrixOrthoRH(5.0f *GetWindowWidth() / GetWindowHeight() , 5, 1.f, 1000.f); 
        Renderer->SetGlobalUniform("mvpMat", (_ProjMat * _ViewMat).m, sizeof(Matrix4x4f));
        Renderer->SetCullMode(CullMode::CULL_NONE);

        return true;
    }

    bool MaterialApplication::OnTerminate()
    {
        cout << "MaterialApplication::OnTerminate" << endl;
        SAFE_DELETE(_Geometry);
        SAFE_DELETE(_ShaderProgram);
        SAFE_DELETE(_Material);
        SAFE_DELETE(_Mesh);
        for (size_t i = 0; i < _Textures.size(); ++i)
        {
            SAFE_DELETE(_Textures[i]);
        }
        return true;
    }

    void MaterialApplication::OnUpdate()
    {
        Matrix4x4f rotMat0; 
        Matrix4x4f rotMat1; 
        static float rot = 0.5;
            //rot += 0.01f;
        float temp = int(rot / PI_2) * PI_2;
        if (rot >= temp)
            rot -= temp;
        rotMat0.MakeRotation(Vector3f::right, rot);
        rotMat1.MakeRotation(Vector3f::up, rot);
        _ShaderProgram->SetUniform("mvpMat", (_ProjMat * _ViewMat * rotMat0 *rotMat1).m, sizeof(Matrix4x4f));
        Renderer->AddRenderInput(&_RenderInput);
    }
}