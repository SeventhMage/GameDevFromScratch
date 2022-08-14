#ifndef _MAGIC_I_MATERIAL_H_
#define _MAGIC_I_MATERIAL_H_

#include "Foundation/Object/IComponent.h"
#include "IShader.h"

namespace Magic
{
    class IMaterial
    {
    public:
        enum EShader
        {
            Vertex = 0,
            Fragment,
            Geometry,
            Tessellation,

            Count,
        };
        virtual ~IMaterial(){}
        virtual void SetShader(IShader *, EShader) = 0;
    };
}

#endif