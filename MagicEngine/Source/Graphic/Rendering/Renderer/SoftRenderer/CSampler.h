#ifndef _MAGIC_C_SAMPLER_H_
#define _MAGIC_C_SAMPLER_H_

#include "Graphic/Rendering/ISampler.h"
#include "CSoftTexture2D.h"

namespace Magic
{
    class CSampler : public ISampler
    {
    public:
        CSampler();
        virtual Color Sample(const Vector2f &uv);
        void SetTexture(CSoftTexture2D *);
    private:
        CSoftTexture2D *_pTexture;
    };
}

#endif