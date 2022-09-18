#include "CSoftRenderer.h"
#include "CSoftIndexBuffer.h"
#include "CSoftVertexBuffer.h"
#include "CSoftRenderTarget.h"
#include "Foundation/Memory/Memory.h"
#include "Foundation/Math/Color.hpp"

#include <iostream>

namespace Magic
{
    CSoftRenderer::CSoftRenderer(int width, int height)
        : CRenderer(width, height), _RenderContext(nullptr), _Rasterizer(new CRasterizer()),
          _FinalRenderTarget(new CSoftRenderTarget(width, height)), _PrimitiveType(PrimitiveType::TRIANGLES),
          _ClearColor(1, 0, 0, 0), _ClearDepth(1.0f), _OnVProgram(nullptr), _OnFProgram(nullptr), _FrontMode(FrontMode::CCW), _CullMode(CullMode::CULL_BACK),
          _RenderStateBits(RenderState::DEFAULT), _ScissorRect(0, 0, width, height), _StencilCmpFunc(CompareFunction::ALWAYS),
          _StencilRef(0), _StencilMask(0xFFFFFFFF), _StencilFailOpt(StencilOperation::KEEP), _StencilZFailOpt(StencilOperation::KEEP),
          _StencilZPassOpt(StencilOperation::KEEP), _DepthCmpFunc(CompareFunction::LESS), _AlphaCmpFunc(CompareFunction::LESS),
          _AlphaCmpValue(1.f), _SrcBlendFactor(BlendFactor::SRC_ALPHA), _DstBlendFactor(BlendFactor::ONE_MINUS_SRC_ALPHA), _BlendOpt(BlendOperation::ADD)
    {
        for (int i = 0; i < CRenderInput::MAX_TEXTURE_NUM; ++i)
        {
            _sampler[i] = NEW CSampler();
        }
        _DrawFunctions[0] = &CSoftRenderer::DrawPoints;
        _DrawFunctions[1] = &CSoftRenderer::DrawLines;
        _DrawFunctions[2] = &CSoftRenderer::DrawLineStrip;
        _DrawFunctions[3] = &CSoftRenderer::DrawTriangles;
        _DrawFunctions[4] = &CSoftRenderer::DrawTriangleFan;
        _DrawFunctions[5] = &CSoftRenderer::DrawTriangleStrip;

        _Compare[CompareFunction::NEVER] = [](float s, float d)->bool{ return false; };
        _Compare[CompareFunction::LESS] = [](float s, float d)->bool{ return s < d; };
        _Compare[CompareFunction::LEQUAL] = [](float s, float d)->bool{ return s <= d; };
        _Compare[CompareFunction::GREATER] = [](float s, float d)->bool{ return s > d; };
        _Compare[CompareFunction::GEQUAL] = [](float s, float d)->bool{ return s >= d; };
        _Compare[CompareFunction::NEQUAL] = [](float s, float d)->bool{ return s != d; };
        _Compare[CompareFunction::ALWAYS] = [](float s, float d)->bool{ return true; };

        _StencilOpt[StencilOperation::KEEP] = [](unsigned int *ptr, int ref) { };
        _StencilOpt[StencilOperation::MAKE_ZERO] = [](unsigned int *ptr, int ref) { *ptr = 0; };
        _StencilOpt[StencilOperation::REPLACE] = [](unsigned int *ptr, int ref) { *ptr = ref;};
        _StencilOpt[StencilOperation::INCREMENT] = [](unsigned int *ptr, int ref) { ++(*ptr);  };
        _StencilOpt[StencilOperation::DECREMENT] = [](unsigned int *ptr, int ref) { --(*ptr); };
        _StencilOpt[StencilOperation::INVERT] = [](unsigned int *ptr, int ref) { *ptr = ~(*ptr); };


        _Blend[BlendOperation::ADD] = [](const Color &s, const Color &d)->Color{ return s + d; };
        _Blend[BlendOperation::SUB] = [](const Color &s, const Color &d)->Color{ return s - d; };
        _Blend[BlendOperation::REVSUB] = [](const Color &s, const Color &d)->Color{ return d - s; };

        _BlendValue[BlendFactor::ONE] = [](const Color &s, const Color &d)->Color{ return Color(1.f, 1.f,1.f, 1.f); };
        _BlendValue[BlendFactor::ZERO] = [](const Color &s, const Color &d)->Color{ return Color(0.f, 0.f, 0.f, 0.f); };
        _BlendValue[BlendFactor::SRC_COLOR] = [](const Color &s,const Color &d )->Color{ return Color(1.f, s.r, s.g, s.b); };
        _BlendValue[BlendFactor::SRC_ALPHA] = [](const Color &s, const Color &d)->Color{ return Color(s.a, s.a, s.a, s.a); };
        _BlendValue[BlendFactor::DST_COLOR] = [](const Color &s, const Color &d)->Color{ return Color(1.f, d.r, d.g, d.b); };
        _BlendValue[BlendFactor::DST_ALPHA] = [](const Color &s, const Color &d)->Color{ return Color(d.a, d.a, d.a, d.a); };
        _BlendValue[BlendFactor::ONE_MINUS_SRC_COLOR] = [](const Color &s, const Color &d)->Color{ return Color(1.f, 1.f - s.r, 1.f - s.g, 1.f - s.b); };
        _BlendValue[BlendFactor::ONE_MINUS_SRC_ALPHA] = [](const Color &s, const Color &d)->Color{ return Color(1.f, 1.f - s.a, 1.f - s.a, 1.f - s.a); };
        _BlendValue[BlendFactor::ONE_MINUS_DST_COLOR] = [](const Color &s, const Color &d)->Color{ return Color(1.f, 1.f - d.r, 1.f - d.g, 1.f - d.b); };
        _BlendValue[BlendFactor::ONE_MINUS_DST_ALPHA] = [](const Color &s, const Color &d)->Color{ return Color(1.f, 1.f - d.a, 1.f - d.a, 1.f - d.a); };
    }

    CSoftRenderer::~CSoftRenderer()
    {
    }

    void CSoftRenderer::SetFrontMode(FrontMode frontMode)
    {
        _FrontMode = frontMode;
    }
    void CSoftRenderer::SetCullMode(CullMode cullMode)
    {
        _CullMode = cullMode;
    }
    void CSoftRenderer::SetRenderState(int stateBits)
    {
        _RenderStateBits &= stateBits;
    }

    void CSoftRenderer::ClearRenderState(int stateBits)
    {
        _RenderStateBits &= ~stateBits;
    }

    void CSoftRenderer::SetScissor(int x, int y, int width, int height)
    {
        _ScissorRect.x = x;
        _ScissorRect.y = y;
        _ScissorRect.z = width;
        _ScissorRect.w = height;
    }

    void CSoftRenderer::SetDepthFunc(CompareFunction cmpFunc)
    {
        _DepthCmpFunc = cmpFunc;
    }
    void CSoftRenderer::SetStencilFunc(CompareFunction func, int reference, int mask)
    {
        _StencilCmpFunc = func;
        _StencilRef = reference;
        _StencilMask = mask;
    }
    void CSoftRenderer::SetStencilOperation(StencilOperation stencilTestFail, StencilOperation depthTestFail, StencilOperation stencilDepthPass)
    {
        _StencilFailOpt = stencilTestFail;
        _StencilZFailOpt = depthTestFail;
        _StencilZPassOpt = stencilDepthPass;
    }

    void CSoftRenderer::SetAlphaFunc(CompareFunction cmpFunc, float value)
    {
        _AlphaCmpFunc = cmpFunc;
        _AlphaCmpValue = value;
    }

    void CSoftRenderer::SetBlendFunc(BlendFactor src, BlendFactor dst, BlendOperation op)
    {
        _SrcBlendFactor = src;
        _DstBlendFactor = dst;
        _BlendOpt = op;
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

    void CSoftRenderer::VertexProcess(IVertexAttribute *vertexAttribute, CSoftShaderProgram *shaderProgram,
                                      const std::vector<unsigned char> &vertDatas, int triIndex, std::vector<unsigned char> &outVert, V2FDatas &data)
    {
        outVert.clear();

        if (_OnVProgram)
            _OnVProgram(&_GlobalUniforms, &shaderProgram->GetUniforms(), (float *)vertDatas.data(), outVert.data());

        int size = 0;
        if (vertexAttribute->HasPosition())
        {
            memcpy(data.position[triIndex].v, outVert.data(), sizeof(Vector4f));
            size += sizeof(Vector4f);
            if (data.position[triIndex].w > 0)
            {
                float invW = 1.0f / data.position[triIndex].w;
                data.position[triIndex].x *= invW;
                data.position[triIndex].y *= invW;
                data.position[triIndex].z *= invW;
            }
        }

        if (vertexAttribute->HasNormal())
        {
            memcpy(data.normal[triIndex].v, outVert.data() + size, sizeof(Vector3f));
            size += sizeof(Vector3f);
        }

        if (vertexAttribute->HasColor())
        {
            memcpy(data.color[triIndex].c, outVert.data() + size, sizeof(Color));
            size += sizeof(Color);
        }

        if (vertexAttribute->HasUV())
        {
            memcpy(data.uv[triIndex].v, outVert.data() + size, sizeof(Vector2f));
            size += sizeof(Vector2f);
        }
    }

    void CSoftRenderer::SwitchScreenSpace(V2FDatas &datas, int triIndex, int width, int height)
    {

        datas.position[triIndex].x = (datas.position[triIndex].x + 1.0f) * 0.5f * width;
        datas.position[triIndex].y = (1 - datas.position[triIndex].y) * 0.5f * height;
    }

    bool CSoftRenderer::ScissorTest(int x, int y)
    {
        if (_RenderStateBits & RenderState::SCISSOR_TEST)
        {
            if (x < _ScissorRect.x || x + _ScissorRect.x > _ScissorRect.z || y < _ScissorRect.y || y + _ScissorRect.y > _ScissorRect.w)
                return false;
        }
        return true;
    }

    bool CSoftRenderer::DepthStencilTest(int x, int y, float invz)
    {
        CSoftRenderTarget *rt = _RenderTarget ? (CSoftRenderTarget *)_RenderTarget : _FinalRenderTarget;
        int width = rt->GetWidth();
        //模板测试

        unsigned int *sptr = nullptr;
        if (_RenderStateBits & RenderState::STENCIL_TEST)
        {
            unsigned int *&sbuffer = rt->GetStencilBuffer();
            sptr = sbuffer + ((y - 1) * width + x);
            if (!_Compare[_StencilCmpFunc](*sptr & _StencilMask, _StencilRef))
            {
                _StencilOpt[_StencilFailOpt](sptr, _StencilRef);
                return false;
            }
        }

        float *zptr = nullptr;
        if (_RenderStateBits & RenderState::DEPTH_TEST)
        {
            float *&zbuffer = rt->GetDepthBuffer();
            zptr = zbuffer + ((y - 1) * width + x);
            if (!_Compare[_DepthCmpFunc](invz, *zptr))
            {
                if (sptr)
                {
                    _StencilOpt[_StencilZFailOpt](sptr, _StencilRef);
                }
                return false;
            }
            else
            {
                if (sptr)
                {
                    _StencilOpt[_StencilZPassOpt](sptr, _StencilRef);
                }
            }
        }
        else
        {
            if (sptr)
            {
                _StencilOpt[_StencilZPassOpt](sptr, _StencilRef);
            }
        }

        if (_RenderStateBits & RenderState::DEPTH_WRITE)
        {
            if (zptr)
                *zptr = invz;
        }

        return true;
    }

    bool CSoftRenderer::AlphaTest(int x, int y, float a)
    {
        if (_RenderStateBits & RenderState::ALPHA_TEST)
        {
            CSoftRenderTarget *rt = _RenderTarget ? (CSoftRenderTarget *)_RenderTarget : _FinalRenderTarget;
            int width = rt->GetWidth();

            unsigned int *&cbuffer = rt->GetColorBuffer();
            if (!_Compare[_AlphaCmpFunc](a, cbuffer[(y - 1) * width + x])) 
                return false;
        }

        return true;
    }

    void CSoftRenderer::Blend(int x, int y, const Color &src)
    {
        CSoftRenderTarget *rt = _RenderTarget ? (CSoftRenderTarget *)_RenderTarget : _FinalRenderTarget;
        int width = rt->GetWidth();

        unsigned int *&cbuffer = rt->GetColorBuffer();
        unsigned int *cptr = cbuffer + (y - 1) * width + x;
        Color dst(*cptr);

        Color srcValue = src * _BlendValue[_SrcBlendFactor](src, dst);
        Color dstValue = dst * _BlendValue[_DstBlendFactor](src, dst);

        *cptr = _Blend[_BlendOpt](srcValue, dstValue).Get32BitColor();
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

        bool hasTexture = false;
        for (int i = 0; i < CRenderInput::MAX_TEXTURE_NUM; ++i)
        {
            ITexture *texture = renderInput->GetTexture(i);
            if (texture)
            {
                ((CSampler *)_sampler[i])->SetTexture((CSoftTexture2D *)texture);
                hasTexture = true;
            }
        }
        //_Rasterizer->SetFProgram(_OnFProgram, &_GlobalUniforms, &shaderProgram->GetUniforms(), hasTexture ? _sampler : nullptr);

        CSoftRenderTarget *rt = _RenderTarget ? (CSoftRenderTarget *)_RenderTarget : _FinalRenderTarget;

        _Rasterizer->SetFragmentProcess([=](float *datas, int x, int y, float invz) -> bool
                                        {
            //裁剪测试
            if (!ScissorTest(x, y))
                return false;

            //深度模板测试
            if (!DepthStencilTest(x, y, invz))
                return false;

            
            Color color = _OnFProgram(&_GlobalUniforms, &shaderProgram->GetUniforms(), hasTexture ? _sampler : nullptr, datas);

            // alpha测试
            if (!AlphaTest(x, y, color.a))
                return false;

            //混合
            Blend(x, y, color);

            return true; });


        _Rasterizer->SetBufferWidthHeight(rt->GetWidth(), rt->GetHeight());

        // todo
        if (indexBuffer && vertexBuffer)
        {
            int indexCount = indexBuffer->GetIndexCount();

            V2FDatas triDatas;
            std::vector<unsigned char> outVert(vertexAttribute->GetOutSize());
            int j = 0;
            for (int i = 0; i < indexCount; ++i)
            {
                int index = indexBuffer->GetIndex(i);
                std::vector<unsigned char> vertDatas = vertexBuffer->GetVertexData(index);

                VertexProcess(vertexAttribute, shaderProgram, vertDatas, j, outVert, triDatas);
                SwitchScreenSpace(triDatas, j, rt->GetWidth(), rt->GetHeight());

                if (j == 2)
                {
                    if (!Culling(Vector3f(triDatas.position[0].v), Vector3f(triDatas.position[1].v), Vector3f(triDatas.position[2].v)))
                    {
                        // draw triangle
                        //_Rasterizer->SetDrawBuffer(rt->GetColorBuffer(), rt->GetWidth(), rt->GetHeight());
                        // _Rasterizer->SetDepthBuffer(rt->GetDepthBuffer());
                        //  _Rasterizer->DrawTriangle(triDatas.position[0], triDatas.position[1], triDatas.position[2], triDatas.uv[0], triDatas.uv[1], triDatas.uv[2],
                        //     triDatas.color[0], triDatas.color[1], triDatas.color[2]);

                        _Rasterizer->DrawTriangle(triDatas.position, triDatas.normal, triDatas.color, triDatas.uv);
                    }
                    j = 0;
                }
                else
                {
                    ++j;
                }
            }
        }
        else if (vertexBuffer)
        {
            int vertexCount = vertexBuffer->GetVertexCount();
            int j = 0;
            V2FDatas triDatas;
            std::vector<unsigned char> outVert(vertexAttribute->GetOutSize());
            for (int i = 0; i < vertexCount; ++i)
            {
                std::vector<unsigned char> vertDatas = vertexBuffer->GetVertexData(i);

                VertexProcess(vertexAttribute, shaderProgram, vertDatas, j, outVert, triDatas);
                SwitchScreenSpace(triDatas, j, rt->GetWidth(), rt->GetHeight());

                if (j == 2 && !Culling(Vector3f(triDatas.position[0].v), Vector3f(triDatas.position[1].v), Vector3f(triDatas.position[2].v)))
                {
                    CSoftRenderTarget *rt = _RenderTarget ? (CSoftRenderTarget *)_RenderTarget : _FinalRenderTarget;

                    // draw triangle
                    _Rasterizer->SetDrawBuffer(rt->GetColorBuffer(), _Width, _Height);
                    _Rasterizer->SetDepthBuffer(rt->GetDepthBuffer());

                    // _Rasterizer->DrawTriangle(triDatas.position[0], triDatas.position[1], triDatas.position[2], triDatas.uv[0], triDatas.uv[1], triDatas.uv[2],
                    //    triDatas.color[0], triDatas.color[1], triDatas.color[2]);
                    _Rasterizer->DrawTriangle(triDatas.position, triDatas.normal, triDatas.color, triDatas.uv);
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
        Vector3f v02 = v2 - v0;
        Vector3f vNormal = _FrontMode == FrontMode::CCW ? v01.CrossProduct(v02) : v02.CrossProduct(v01);
        vNormal.Normalize();
        Vector3f vCamDir(0, 0, -1);
        return _CullMode == CullMode::CULL_BACK ? (vNormal.DotProduct(vCamDir) < 0) : (vNormal.DotProduct(vCamDir) > 0);
    }

    IShaderProgram *CSoftRenderer::CreateShaderProgram(const char *vertShader, const char *fragShader) const
    {
        return NEW CSoftShaderProgram(vertShader, fragShader);
    }

    ITexture *CSoftRenderer::CreateTexture(const char *fullPath) const
    {
        return NEW CSoftTexture2D(fullPath);
    }
}