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
        IVertexBuffer *vertexBuffer = Renderer->CreateVertexBuffer();
        IIndexBuffer *indexBuffer = Renderer->CreateIndexBuffer();

        float Cube[] = { 
            //position
            -1.f, -1.f, 1.f,  
            1.f, -1.f, 1.f, 
            1.f, 1.f, 1.f, 
            -1.f, 1.f, 1.f,
            1.f, -1.f, -1.f,
            -1.f, -1.f, -1.f,
            -1.f, 1.f, -1.f,
            1.f, 1.f, -1.f,

            //uv
            0, 0,
            1, 0,
            1, 1,
            0, 1,
            0, 0,
            1, 0,
            1, 1,
            0, 1,
            };
  
        unsigned int indices[] = {0, 1, 2, 0, 2, 3, 
        4, 5, 6, 4, 6, 7, 
        1, 4, 7, 1, 7, 2, 
        5, 0, 3, 5, 3, 6, 
        //3, 2, 7, 3, 7, 6, 
        //1, 0, 5, 1, 5, 4
        };
 
        vertexBuffer->BufferData(Cube, sizeof(Cube), 8); 
        vertexBuffer->GetAttribute()->SetPositionAttr(0, sizeof(float) * 3);
        vertexBuffer->GetAttribute()->SetUVAttr(sizeof(float) * 8 * 3, sizeof(float) * 2);

        indexBuffer->BufferData(indices, sizeof(indices), sizeof(indices) / sizeof(unsigned int));

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
        static float rot = 0;
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