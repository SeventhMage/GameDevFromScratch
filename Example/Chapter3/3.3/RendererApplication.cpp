#include <iostream>
#include "RendererAppliaction.h"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Math.hpp"
#include "ShaderProgram.hpp"


using namespace std;

namespace Magic
{
    IMPLEMENT_APP_INITIALIZE(RendererApplication);
    IMPLEMENT_APP_TERMINATE(RendererApplication);

    bool RendererApplication::OnInitialize()
    { 
        cout << "RendererApplication::OnInitialize" << endl;
        IVertexBuffer *vertexBuffer = Renderer->CreateVertexBuffer();
        IIndexBuffer *indexBuffer = Renderer->CreateIndexBuffer();

        float triangle[] = { -1.f, -1.f, -0.f,         1.f, 1.f, 1.f,      0.f, 0.f,
            1.f, -1.f, -0.f,       1.0f, 1.0f, 1.0f,         1.f, 0.f,
            0.f, 1.f, -0.f,        1.0f, 1.0f, 1.0f,      0.5f, 1.f
            };

        vertexBuffer->BufferData(triangle, sizeof(triangle), 3); 
        vertexBuffer->GetAttribute()->SetPositionAttr(0, sizeof(float) * 8);
        vertexBuffer->GetAttribute()->SetColorAttr(sizeof(float) * 3, sizeof(float) * 8);
        vertexBuffer->GetAttribute()->SetUVAttr(sizeof(float) * 6, sizeof(float) * 8);

        _Geometry = NEW CGeometry(vertexBuffer, nullptr);
        _Texture = Renderer->CreateTexture("crate.tga");

        _ShaderProgram_0 = Renderer->CreateShaderProgram("VertexShader", "FragmentShader");
        _RenderInput_0.SetGeometry(_Geometry); 
        _RenderInput_0.SetShaderProgram(_ShaderProgram_0);
        _RenderInput_0.SetTexture(0, _Texture);

        _ShaderProgram_1 = Renderer->CreateShaderProgram("VertexShader", "FragmentShader");
        _RenderInput_1.SetGeometry(_Geometry); 
        _RenderInput_1.SetShaderProgram(_ShaderProgram_1);
        _RenderInput_1.SetTexture(0, _Texture);


        Renderer->SetClearColor(0, 0, 0); 
        _ViewMat.BuildCameraLookAtMatrix(Vector3f(0, 0, 5.f), Vector3f(0, 0, -1), Vector3f(0, 1, 0));
        _ProjMat.BuildProjectionMatrixPerspectiveFovRH(PI / 3.f,   1.0f * GetWindowWidth() / GetWindowHeight(), 1.0f, 100.f);
        //_ProjMat.BuildProjectionMatrixOrthoRH(5.0f *GetWindowWidth() / GetWindowHeight() , 5, 1.f, 1000.f); 
        Renderer->SetGlobalUniform("mvpMat", (_ProjMat* _ViewMat).m, sizeof(Matrix4x4f));
        Renderer->SetCullMode(CullMode::CULL_NONE);
        return true;
    }

    bool RendererApplication::OnTerminate()
    {
        cout << "RendererApplication::OnTerminate" << endl;
        SAFE_DELETE(_Geometry);
        SAFE_DELETE(_ShaderProgram_0);
        SAFE_DELETE(_ShaderProgram_1);
        return true;
    }

    void RendererApplication::OnUpdate()
    {
        Matrix4x4f rotMat0; 
        Matrix4x4f rotMat1; 
        static float rot = 0;
            rot += 0.03f;
        float temp = int(rot / PI_2) * PI_2;
        if (rot >= temp)
            rot -= temp;
        rotMat0.MakeRotation(Vector3f::right, rot);
        rotMat1.MakeRotation(Vector3f::up, rot);
        _ShaderProgram_0->SetUniform("mvpMat", (_ProjMat * _ViewMat * rotMat0).m, sizeof(Matrix4x4f));
        Renderer->AddRenderInput(&_RenderInput_0);
        _ShaderProgram_1->SetUniform("mvpMat", (_ProjMat * _ViewMat * rotMat1).m, sizeof(Matrix4x4f));
        Renderer->AddRenderInput(&_RenderInput_1);
    }
}