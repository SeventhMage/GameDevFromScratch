#ifndef _MAGIC_C_SOFT_RENDERER_H_
#define _MAGIC_C_SOFT_RENDERER_H_

#include <vector>

#include "Graphic/Rendering/CRenderer.h"
#include "Graphic/Rendering/IRenderInput.h"
#include "Graphic/Rendering/CSoftShaderProgram.h"
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
        virtual void SetRenderState(int stateBits, bool enable) override;
        virtual void SetDepthFunc(CompareFunction) override;
        virtual void SetStencilFunc(CompareFunction func, int reference, int mask) override;
        virtual void SetStencilOperation(StencilOperation stencilTestFail, StencilOperation depthTestFail, StencilOperation stencilDepthPass) override;
        virtual void SetClearColor(float r, float g, float b) override;
        virtual void SetClearDepth(float depth) override;
        virtual void Clear(int bufferBits) override;
        virtual IVertexBuffer *CreateVertexBuffer() override;
        virtual IIndexBuffer *CreateIndexBuffer() override;
        virtual void Draw(IRenderInput *) override;
        virtual void End() override;
        virtual void OnViewportChange() override;
    private:

        typedef void (CSoftRenderer::*DrawFunction)(IRenderInput *);
        void DrawPoints(IRenderInput *);
        void DrawLines(IRenderInput *);
        void DrawLineStrip(IRenderInput *);
        void DrawTriangles(IRenderInput *);
        void DrawTriangleFan(IRenderInput *);
        void DrawTriangleStrip(IRenderInput *);

        void DrawBuffer();

        bool Culling(const Vector3f &v0, const Vector3f &v1, const Vector3f &v2);
    private:
        IRenderContext *_RenderContext;
        CRasterizer *_Rasterizer;
        CSoftRenderTarget *_FinalRenderTarget;
        PrimitiveType _PrimitiveType;
        DrawFunction _DrawFunctions[PrimitiveType::Count];

        Color _ClearColor;
        float _ClearDepth;

        VProgram _OnVProgram;
        FProgram _OnFProgram;

        FrontMode _FrontMode;
        CullMode _CullMode;
        

    };
}

#endif