#ifndef _MAGIC_I_RENDER_INPUT_H_
#define _MAGIC_I_RENDER_INPUT_H_

#include "IGeometry.h"
#include "IShaderProgram.h"
#include "ITexture.h"

namespace Magic
{
    class IRenderInput
    {
    public:
        virtual ~IRenderInput(){}
        virtual void SetGeometry(IGeometry *) = 0;
        virtual void SetShaderProgram(IShaderProgram *) = 0;
        virtual void SetTexture(int slot, ITexture *) = 0;
        virtual IGeometry *GetGeometry() const = 0;
        virtual ITexture *GetTexture(int slot) const = 0;
        virtual IShaderProgram *GetShaderProgram() const = 0;
        virtual void Prepare() = 0;
    };
}

#endif