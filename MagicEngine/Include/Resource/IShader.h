#ifndef _MAGIC_I_SHADER_H_
#define _MAGIC_I_SHADER_H_

#include "IResource.h"

namespace Magic
{
    class IShader : public IResource
    {
    public:
        enum ShaderType
        {
            Vertex = 0,
            Fragment,
            Geometry,
            Tessellation,
            Compute,

            Count,
        };

        virtual Type GetType() const { return SHADER; }
    };
}

#endif