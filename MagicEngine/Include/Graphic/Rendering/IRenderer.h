#ifndef _MAGIC_I_RENDERER_H_
#define _MAGIC_I_RENDERER_H_ 

#include "RenderDefine.h"
#include "IGeometry.h"
#include "IRenderTarget.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "IRenderInput.h"
#include "IRenderContext.h"

namespace Magic
{
    enum RendererType
    {
        Software,
        Vulkan,
        OpenGL,
        GLES,
        DX12,
    };
    class IRenderer
    {
    public:
        virtual ~IRenderer(){}
        virtual void InitDriver(IRenderContext *) = 0;
        virtual void CleanDriver() = 0;
        virtual RendererType GetRendererType() const = 0;
        virtual void SetFrontMode(FrontMode) = 0;
        virtual void SetCullMode(CullMode) = 0;
        virtual void SetRenderState(int stateBits) = 0;
        virtual void ClearRenderState(int stateBits) = 0;
        virtual void SetScissor(int x, int y, int width, int height) = 0;
        virtual void SetStencilFunc(CompareFunction func, int reference, int mask) = 0;
        virtual void SetStencilOperation(StencilOperation stencilTestFail, StencilOperation depthTestFail, StencilOperation stencilDepthPass) = 0;
        virtual void SetDepthFunc(CompareFunction cmpFunc) = 0;
        virtual void SetAlphaFunc(CompareFunction cmpFunc, float value) = 0;
        virtual void SetBlendFunc(BlendFactor src, BlendFactor dst, BlendOperation op) = 0;
        virtual void SetClearColor(float r, float g, float b) = 0;
        virtual void SetClearDepth(float depth) = 0;
        virtual void Clear(int bufferBits = BufferBit::ALL) = 0;
        virtual IVertexBuffer *CreateVertexBuffer() = 0;
        virtual IIndexBuffer *CreateIndexBuffer() = 0;
        virtual void Draw(IRenderInput *renderInput) = 0;
        virtual void SetRenderTarget(IRenderTarget *) = 0;
        virtual void AddRenderInput(IRenderInput *) = 0;
        virtual void Resize(int width, int height) = 0;
        virtual void SetGlobalUniform(const char *name, const void *data, int size) = 0;
        virtual void Begin() = 0;
        virtual void Render() = 0;
        virtual void End() = 0;
        virtual IShaderProgram *CreateShaderProgram(const char *vertShader, const char *fragShader) const = 0;
        virtual ITexture *CreateTexture(const char *fullPath) const = 0;
    };
}

#endif