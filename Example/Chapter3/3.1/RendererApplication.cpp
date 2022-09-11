#include <iostream>
#include "RendererAppliaction.h"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Matrix4x4.hpp"
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

        float triangle[] = { -1.f, -1.f, -10.f, 1.f, 0.f, 0.f,
            1.f, -1.f, -10.f, 0.0f, 1.0f, 0.0f,
            0.f, 1.f, -10.f, 0.0f, 0.0f, 1.0f,
            };
        vertexBuffer->BufferData(triangle, sizeof(triangle), sizeof(triangle) / (6 * sizeof(float)));
        vertexBuffer->GetAttribute()->SetPositionAttr(0, sizeof(float) * 6);
        vertexBuffer->GetAttribute()->SetColorAttr(sizeof(float) * 3, sizeof(float) * 6);

        _Geometry = NEW CGeometry(vertexBuffer, nullptr);
        _RenderInput.SetGeometry(_Geometry);
        _ShaderProgram = Renderer->CreateShaderProgram("VertexShader", "FragmentShader");
        _RenderInput.SetShaderProgram(_ShaderProgram);
        _RenderInput.SetTexture(0, nullptr);
        Renderer->SetClearColor(0, 0, 0);
        Matrix4x4f vMat, proMat;
        vMat.BuildCameraLookAtMatrix(Vector3f(0, 0, 0), Vector3f(0, 0, -1), Vector3f(0, 1, 0));
        //proMat.BuildProjectionMatrixPerspectiveFovRH(PI / 6.f,   1.0f * GetWindowWidth() / GetWindowHeight(), 1.0f, 1000.f);
        proMat.BuildProjectionMatrixOrthoRH(5.0f *GetWindowWidth() / GetWindowHeight() , 5, 1.f, 1000.f); 
        Renderer->SetGlobalUniform("mvpMat", (proMat * vMat).m, sizeof(Matrix4x4f));
        return true;
    }

    bool RendererApplication::OnTerminate()
    {
        cout << "RendererApplication::OnTerminate" << endl;
        SAFE_DELETE(_Geometry);
        SAFE_DELETE(_ShaderProgram);
        return true;
    }

    void RendererApplication::OnUpdate()
    {

        Renderer->AddRenderInput(&_RenderInput);
    }
}