#ifndef _MAGIC_C_SAMPLER_H_
#define _MAGIC_C_SAMPLER_H_

#include "Graphic/Rendering/ISampler.h"
#include "Graphic/Rendering/ITexture.h"

namespace Magic
{
    class CSampler : public ISampler
    {
    public:
        CSampler();
        virtual Color Sample(const Vector2f &uv);
        void SetTexture(ITexture *);
    private:
        ITexture *_pTexture;
    };
}

#endif