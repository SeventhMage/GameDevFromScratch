#ifndef _MAGIC_C_RENDER_INPUT_H_
#define _MAGIC_C_RENDER_INPUT_H_

#include "IRenderInput.h"

namespace Magic
{
    class CRenderInput : public IRenderInput
    {
    public:
        CRenderInput();
        virtual ~CRenderInput();
        virtual void SetGeometry(IGeometry *);
        virtual void SetShaderProgram(IShaderProgram *);
        virtual void SetTexture(int slot, ITexture *);
        virtual IGeometry *GetGeometry() const;
        virtual ITexture *GetTexture(int slot) const;
        virtual IShaderProgram *GetShaderProgram() const;
        virtual void Prepare();
        static const int MAX_TEXTURE_NUM = 8;
    private:
        IGeometry *_Geometry;
        IShaderProgram *_ShaderProgram;
        ITexture *_Textures[MAX_TEXTURE_NUM];
    };
}

#endif