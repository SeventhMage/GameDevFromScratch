#include "CSoftRenderer.h"
#include "CSoftIndexBuffer.h"
#include "CSoftVertexBuffer.h"
#include "CSoftRenderTarget.h"
#include "Foundation/Memory/Memory.h"

#include <iostream>

namespace Magic
{
    CSoftRenderer::CSoftRenderer(int width, int height)
        : CRenderer(width, height), _RenderContext(nullptr), _Rasterizer(new CRasterizer()), 
            _FinalRenderTarget(new CSoftRenderTarget(width, height)), _PrimitiveType(PrimitiveType::TRIANGLES),
            _ClearColor(1, 0, 0, 0), _ClearDepth(1.0f), _FrontMode(FrontMode::CCW), _CullMode(CullMode::CULL_BACK)
    {
        
        _DrawFunctions[0] = &CSoftRenderer::DrawPoints;
        _DrawFunctions[1] = &CSoftRenderer::DrawLines;
        _DrawFunctions[2] = &CSoftRenderer::DrawLineStrip;
        _DrawFunctions[3] = &CSoftRenderer::DrawTriangles;
        _DrawFunctions[4] = &CSoftRenderer::DrawTriangleFan;
        _DrawFunctions[5] = &CSoftRenderer::DrawTriangleStrip;
    }

    CSoftRenderer::~CSoftRenderer()
    {
    }

    void CSoftRenderer::SetFrontMode(FrontMode)
    {
    }
    void CSoftRenderer::SetCullMode(CullMode)
    {
    }
    void CSoftRenderer::SetRenderState(int stateBits, bool enable)
    {
    }
    void CSoftRenderer::SetDepthFunc(CompareFunction)
    {
    }
    void CSoftRenderer::SetStencilFunc(CompareFunction func, int reference, int mask)
    {
    }
    void CSoftRenderer::SetStencilOperation(StencilOperation stencilTestFail, StencilOperation depthTestFail, StencilOperation stencilDepthPass)
    {
    }
    void CSoftRenderer::SetClearColor(float r, float g, float b)
    {
        _ClearColor.r = r;
        _ClearColor.g = g;
        _ClearColor.b = b;
        _ClearColor.a = 1.0f;
    }
    void CSoftRenderer::SetClearDepth(float depth)
    {
        _ClearDepth = depth;
    }
    void CSoftRenderer::Clear(int bufferBits)
    {
        int size = _FinalRenderTarget->GetWidth() * _FinalRenderTarget->GetHeight();
        if (bufferBits & BufferBit::COLOR_BIT)
        {
            auto buffer = _FinalRenderTarget->GetColorBuffer();
            int clearColor32 = _ClearColor.Get32BitColor();
            for (int i = 0; i < size; ++i)
                *buffer++ = clearColor32;
        }

        if (bufferBits & BufferBit::DEPTH_BIT)
        {
            auto buffer = _FinalRenderTarget->GetDepthBuffer();
            for (int i = 0; i < size; ++i)
                *buffer++ = _ClearDepth;
        }

        if (bufferBits & BufferBit::STENCIL_BIT)
        {
            auto buffer = _FinalRenderTarget->GetStencilBuffer();
            for (int i = 0; i < size; ++i)
                *buffer++ = 0;
        }
    }

    IVertexBuffer *CSoftRenderer::CreateVertexBuffer()
    {
        return NEW CSoftVertexBuffer();
    }
    IIndexBuffer *CSoftRenderer::CreateIndexBuffer()
    {
        return NEW CSoftIndexBuffer();
    }

    void CSoftRenderer::End()
    {
        DrawBuffer();
        _RenderInputs.clear();
    }
    void CSoftRenderer::Draw(IRenderInput *renderInput)
    {
        renderInput->Prepare();
        (this->*_DrawFunctions[_PrimitiveType])(renderInput);
    }

    void CSoftRenderer::DrawPoints(IRenderInput *)
    {
    }
    void CSoftRenderer::DrawLines(IRenderInput *)
    {
    }
    void CSoftRenderer::DrawLineStrip(IRenderInput *)
    {
    }
    void CSoftRenderer::DrawTriangles(IRenderInput *renderInput)
    {
        IGeometry *geometry = renderInput->GetGeometry();
        CSoftShaderProgram *shaderProgram = (CSoftShaderProgram *)renderInput->GetShaderProgram();
        CSoftVertexBuffer *vertexBuffer = (CSoftVertexBuffer *)geometry->GetVertexBuffer();
        CSoftIndexBuffer *indexBuffer = (CSoftIndexBuffer *)geometry->GetIndexBuffer();
        IVertexAttribute *vertexAttribute = vertexBuffer->GetAttribute();

        shaderProgram->Prepare();
        _OnVProgram = shaderProgram->GetVertexProgram();
        _OnFProgram = shaderProgram->GetFragmentProgram();

        // todo
        if (indexBuffer && vertexBuffer)
        {
        }
        else if (vertexBuffer)
        {
            int vertexCount = vertexBuffer->GetVertexCount();
            int j = 0;
            Vector4f trianglePos[3];
            Vector3f triangleNormal[3];
            Vector3f triangleColor[3];
            Vector2f triangleUV[3];
            std::vector<unsigned char> outVert;
            for (int i = 0; i < vertexCount; ++i)
            {
                std::vector<unsigned char> vertDatas = vertexBuffer->GetVertexData(i);
                outVert.clear();
                outVert.resize(vertDatas.size() * 2);

                if (_OnVProgram)
                    _OnVProgram(&_GlobalUniforms, &shaderProgram->GetUniforms(), (float *)vertDatas.data(), outVert.data()); 


                int size = 0;
                if (vertexAttribute->HasPosition())
                {
                    memcpy(trianglePos[j].v, outVert.data(), sizeof(Vector4f));
                    size += sizeof(Vector4f);
                    if (trianglePos[j].w > 0)
                    {
                        float invW = 1.0f / trianglePos[j].w;
                        trianglePos[j].x *= invW; 
                        trianglePos[j].y *= invW; 
                        trianglePos[j].z *= invW; 
                    }
                }
                
                if (vertexAttribute->HasNormal())
                {
                    memcpy(triangleNormal[j].v, outVert.data() + size, sizeof(Vector3f));
                    size += sizeof(Vector3f);
                }

                if (vertexAttribute->HasColor())
                {
                    memcpy(triangleColor[j].v, outVert.data() + size, sizeof(Vector3f));
                    size += sizeof(Vector3f);
                }

                if (vertexAttribute->HasUV())
                {
                    memcpy(triangleUV[j].v, outVert.data() + size, sizeof(Vector3f));
                    size += sizeof(Vector2f);
                }

                if (j == 2 && !Culling(Vector3f(trianglePos[0].v), Vector3f(trianglePos[1].v), Vector3f(trianglePos[2].v)))
                {
                    CSoftRenderTarget *rt = _RenderTarget ? (CSoftRenderTarget *)_RenderTarget : _FinalRenderTarget;

                    //转换到屏幕空间
                    for (int i = 0; i < 3; ++i)
                    {
                        trianglePos[i].x = (trianglePos[i].x + 1.0f) * 0.5f * rt->GetWidth();
                        trianglePos[i].y = (1 - trianglePos[i].y) * 0.5f * rt->GetHeight();
                    }

                    // draw triangle
                    _Rasterizer->SetDrawBuffer(rt->GetColorBuffer(), _Width, _Height);
                    _Rasterizer->SetDepthBuffer(rt->GetDepthBuffer());

                    _Rasterizer->DrawTriangle(trianglePos[0], trianglePos[1], trianglePos[2], triangleUV[0], triangleUV[1], triangleUV[2], 
                        Color(1.f, triangleColor[0].x, triangleColor[0].y, triangleColor[0].z), Color(1.f, triangleColor[1].x, triangleColor[1].y, triangleColor[1].z),
                        Color(1.f, triangleColor[2].x, triangleColor[2].y, triangleColor[2].z));
                    j = 0;
                }
                else
                {
                    ++j;
                }
            }
        }
    }
    void CSoftRenderer::DrawTriangleFan(IRenderInput *)
    {
    }
    void CSoftRenderer::DrawTriangleStrip(IRenderInput *)
    {
    }

    bool CSoftRenderer::Culling(const Vector3f &v0, const Vector3f &v1, const Vector3f &v2)
    {
        if (_CullMode == CullMode::CULL_NONE)
            return false;
        Vector3f v01 = v1 - v0;
        Vector3f v02  = v2 - v0;
        Vector3f vNormal = _FrontMode == FrontMode::CCW ? v01.CrossProduct(v02) : v02.CrossProduct(v01);
        vNormal.Normalize();
        Vector3f vCamDir(0, 0, 1);
        return _CullMode == CullMode::CULL_BACK ? (vNormal.DotProduct(vCamDir) < 0) : (vNormal.DotProduct(vCamDir) > 0);
    }

    IShaderProgram *CSoftRenderer::CreateShaderProgram(const char *vertShader, const char *fragShader) const
    {
        return NEW CSoftShaderProgram(vertShader, fragShader);
    }
}