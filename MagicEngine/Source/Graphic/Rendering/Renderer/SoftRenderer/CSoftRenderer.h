#ifndef _MAGIC_C_SOFT_RENDERER_H_
#define _MAGIC_C_SOFT_RENDERER_H_

#include <vector>
#include <functional>

#include "Graphic/Rendering/CRenderer.h"
#include "Graphic/Rendering/CRenderInput.h"
#include "CSoftShaderProgram.h"
#include "Foundation/Math/Color.hpp"
#include "CSoftRenderTarget.h"
#include "CRasterizer.h"
#include "CSampler.h"

namespace Magic
{
    // 背面剔除 在屏幕空间 107
    class CSoftRenderer : public CRenderer
    {
    public:
        CSoftRenderer(int width, int height);
        ~CSoftRenderer();
        virtual void InitDriver(IRenderContext *) override;
        virtual void CleanDriver() override;
        virtual RendererType GetRendererType() const { return RendererType::Software; }
        virtual void SetFrontMode(FrontMode) override;
        virtual void SetCullMode(CullMode) override;
        virtual void SetRenderState(int stateBits) override;
        virtual void ClearRenderState(int stateBits) override;
        virtual void SetScissor(int x, int y, int width, int height) override;
        virtual void SetStencilFunc(CompareFunction func, int reference, int mask) override;
        virtual void SetStencilOperation(StencilOperation stencilTestFail, StencilOperation depthTestFail, StencilOperation stencilDepthPass) override;
        virtual void SetDepthFunc(CompareFunction) override;
        virtual void SetAlphaFunc(CompareFunction cmpFunc, float value);
        virtual void SetBlendFunc(BlendFactor src, BlendFactor dst, BlendOperation op) override;
        virtual void SetClearColor(float r, float g, float b) override;
        virtual void SetClearDepth(float depth) override;
        virtual void Clear(int bufferBits) override;
        virtual IVertexBuffer *CreateVertexBuffer() override;
        virtual IIndexBuffer *CreateIndexBuffer() override;
        virtual void Draw(IRenderInput *) override;
        virtual void End() override;
        virtual void OnViewportChange() override;
        virtual IShaderProgram *CreateShaderProgram(const char *vertShader, const char *fragShader) const override;
        virtual ITexture *CreateTexture(const char *fullPath) const override;

    private:

        typedef struct
        {
            Vector4f position[3];
            Vector3f normal[3];
            Color color[3];
            Vector2f uv[3];
        }V2FDatas;

        typedef void (CSoftRenderer::*DrawFunction)(IRenderInput *);
        void DrawPoints(IRenderInput *);
        void DrawLines(IRenderInput *);
        void DrawLineStrip(IRenderInput *);
        void DrawTriangles(IRenderInput *);
        void DrawTriangleFan(IRenderInput *);
        void DrawTriangleStrip(IRenderInput *);

        void DrawBuffer();

        bool Culling(const Vector3f &v0, const Vector3f &v1, const Vector3f &v2);

        void VertexProcess(IVertexAttribute *vertexAttribute, CSoftShaderProgram *shaderProgram, const std::vector<unsigned char> &vertDatas, 
            int triIndex, std::vector<unsigned char> &outVert, V2FDatas &datas);
        void SwitchScreenSpace(V2FDatas &datas, int triIndex, int width, int height);

        bool ScissorTest(int x, int y);
        bool DepthStencilTest(int x, int y, float invz); 
        bool AlphaTest(int x, int y, float a);
        void Blend(int x, int y, const Color &src);
    private:
        IRenderContext *_RenderContext;
        CRasterizer *_Rasterizer;
        CSoftRenderTarget *_FinalRenderTarget;
        PrimitiveType _PrimitiveType;
        DrawFunction _DrawFunctions[PrimitiveType::PT_COUNT];

        ISampler *_sampler[CRenderInput::MAX_TEXTURE_NUM];

        std::function<bool(float, float)> _Compare[CompareFunction::CF_COUNT];
        std::function<void(unsigned int *, int)> _StencilOpt[StencilOperation::SO_COUNT];
        std::function<Color(const Color&, const Color&)> _Blend[BlendOperation::BO_COUNT];
        std::function<Color(const Color&, const Color&)> _BlendValue[BlendFactor::BF_COUNT];

        Color _ClearColor;
        float _ClearDepth;

        VProgram _OnVProgram;
        FProgram _OnFProgram;

        FrontMode _FrontMode;
        CullMode _CullMode;
        

        int _RenderStateBits;
        Vector4i _ScissorRect;

        CompareFunction _StencilCmpFunc;
        int _StencilRef;
        int _StencilMask;
        StencilOperation _StencilFailOpt;
        StencilOperation _StencilZFailOpt;
        StencilOperation _StencilZPassOpt;

        CompareFunction _DepthCmpFunc;

        CompareFunction  _AlphaCmpFunc;
        float _AlphaCmpValue;

        BlendFactor _SrcBlendFactor;
        BlendFactor _DstBlendFactor;
        BlendOperation _BlendOpt;


    };
}

#endif