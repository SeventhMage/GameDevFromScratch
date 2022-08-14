#ifndef _MAGIC_I_SHADER_H_
#define _MAGIC_I_SHADER_H_

namespace Magic
{
    class IShader
    {
    public:
        enum Type
        {
            Vertex = 0,
            Fragment,
            Geometry,
            Tessellation,
            Compute,

            Count,
        };
    };
}

#endif