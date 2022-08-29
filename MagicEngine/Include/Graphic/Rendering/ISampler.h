#ifndef _MAGIC_I_SAMPLER_H_
#define _MAGIC_I_SAMPLER_H_

#include "Foundation/Math/Color.hpp"
#include "Foundation/Math/Vector2.hpp"

namespace Magic
{
    class ISampler
    {
    public:
        virtual ~ISampler(){}
        virtual Color Sample(Vector2f uv);
    };
}


#endif