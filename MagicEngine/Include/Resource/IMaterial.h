#ifndef _MAGIC_I_MATERIAL_H_
#define _MAGIC_I_MATERIAL_H_

#include "IResource.h"
#include "IShader.h"

namespace Magic
{
    class IMaterial : public IResource
    {
    public:
        virtual ~IMaterial(){}
        virtual Type GetType() const { return MATERIAL; }
        virtual void SetName(const char *name) = 0;
        virtual void SetVertShader(const char *name) = 0;
        virtual void SetFragShader(const char *name) = 0;
        virtual void SetTexture(int slot, const char *name) = 0;
        virtual void SetTransparent(bool transparent) = 0;
        virtual const char *GetName() const = 0;
        virtual const char *GetVertShader() const = 0;
        virtual const char *GetFragShader() const = 0;
        virtual const char *GetTexture(int slot) const = 0;
        virtual int GetTextureQuantity() const = 0;
        virtual bool IsTransparent() const = 0;
    };
}

#endif