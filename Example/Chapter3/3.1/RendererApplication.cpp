#include <iostream>
#include "RendererAppliaction.h"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Matrix4x4.hpp"
#include "Foundation/Math/Color.hpp"
#include "Graphic/Rendering/ISampler.h"
#include "Graphic/Rendering/CSoftShaderProgram.h"

using namespace std;

namespace Magic
{

    void VertexShader(const void *globalUniforms, const void *uniforms, const void *datas, unsigned char*out)
    {
        UniformMap globalU= *((UniformMap*)globalUniforms);
        UniformMap u = *((UniformMap*)uniforms);
        Matrix4x4f mvpMat4(globalU["mvpMat"].data());

        Vector3f inPosition;
        Vector3f inColor;
        memcpy(inPosition.v, datas, sizeof(inPosition.v));
        memcpy(inColor.v, (unsigned char *)datas + sizeof(Vector3f), sizeof(inColor.v));

        Vector4f outPosition = mvpMat4 * Vector4f(inPosition.x, inPosition.y, inPosition.z, 1.0f);

        memcpy(out, &outPosition, sizeof(outPosition));
        memcpy(out + sizeof(outPosition), &inColor, sizeof(inColor));
    }

    Color FragmentShader(const void *uniforms, ISampler **, const void *datas)
    {
        Vector3f inColor;
        memcpy(inColor.v, datas, sizeof(inColor.v));

        return Color(1.0f, inColor.x, inColor.y, inColor.z);
    }

    IMPLEMENT_APP_INITIALIZE(RendererApplication);

    bool RendererApplication::OnInitialize()
    {
        cout << "RendererApplication::OnInitialize" << endl;
        IVertexBuffer *vertexBuffer = Renderer->CreateVertexBuffer();
        IIndexBuffer *indexBuffer = Renderer->CreateIndexBuffer();

        float triangle[] = { -10.f, -10.f, -100.f, 1.f, 0.f, 0.f,
            10.f, -10.f, -100.f, 0.0f, 1.0f, 0.0f,
            0.f, 10.f, -100.f, 0.0f, 0.0f, 1.0f,
            };
        vertexBuffer->BufferData(triangle, sizeof(triangle), sizeof(triangle) / (6 * sizeof(float)));
        vertexBuffer->GetAttribute()->SetPositionAttr(0, sizeof(float) * 6);
        vertexBuffer->GetAttribute()->SetColorAttr(sizeof(float) * 3, sizeof(float) * 6);

        _Geometry = NEW CGeometry(vertexBuffer, nullptr);
        _RenderInput.SetGeometry(_Geometry);
        IShaderProgram *shaderProgram = nullptr;
        if (Renderer->GetRendererType() == RendererType::Software)
        {
            shaderProgram = NEW CSoftShaderProgram(VertexShader, FragmentShader);
        }
        _RenderInput.SetShaderProgram(shaderProgram);
        _RenderInput.SetTexture(0, nullptr);
        Renderer->SetClearColor(0, 0, 0);
        Matrix4x4f vMat, proMat;
        vMat.BuildCameraLookAtMatrix(Vector3f(0, 0, 0), Vector3f(0, 0, -1), Vector3f(0, 1, 0));
        proMat.BuildProjectionMatrixOrthoRH(PI / 6.f,   1.0f * GetWindowHeight() / GetWindowWidth(), 1.0f, 1000.f);
        Renderer->SetGlobalUniform("mvpMat", (proMat * vMat).m, sizeof(Matrix4x4f));
        return true;
    }

    bool RendererApplication::OnTerminate()
    {
        cout << "RendererApplication::OnTerminate" << endl;
        SAFE_DELETE(_Geometry);
        return true;
    }

    void RendererApplication::OnUpdate()
    {

        Renderer->AddRenderInput(&_RenderInput);
    }
}