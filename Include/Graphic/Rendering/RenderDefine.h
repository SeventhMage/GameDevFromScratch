#ifndef _MAGIC_RENDER_STATE_H_
#define _MAGIC_RENDER_STATE_H_

namespace Magic
{

    enum FrontMode
    {
        CCW,
        CW,
    };

    enum CullMode
    {
        CULL_NONE,
        CULL_BACK,
        CULL_FRONT,
    };

    enum ERenderState
    {
        ALPHA_TEST = 0x00000001,
        DEPTH_TEST = 0x00000001 << 1,
        STENCIL_TEST = 0x00000001 << 2,
        DEPTH_WRITE = 0x00000001 << 3,
        STENCIL_WRITE = 0x00000001 << 4,
    };

    enum BufferBit
    {
        COLOR_BIT = 0x00000001,
        DEPTH_BIT = 0x00000002,
        STENCIL_BIT = 0x00000004,
        ALL = COLOR_BIT | DEPTH_BIT | STENCIL_BIT,
    };

    enum CompareFunction
    {
        NEVER = 0x00000001,
        LESS = 0x00000001 << 2,
        GREATER = 0x00000001 << 3,
        EQUAL = 0x00000001 << 4,
        NEQUAL = 0x00000001 << 5,
        LEQUAL = 0x00000001 << 6,
        GEQUAL = 0x00000001 << 7,
        ALWAYS = 0x00000001 << 8,
    };

    enum TestState
    {
        DEPTH_FAIL,
        STENCIL_FAIL,
        STENCIL_DEPTH_PASS,
    };

    enum StencilOperation
    {
        KEEP = 0x00000001,
        ZERO = 0x00000001 << 1,
        REPLACE = 0x00000001 << 2,
        INCREMENT = 0x00000001 << 3,
        DECREMENT = 0x00000001 << 4,
        INVERT = 0x00000001 << 5,
    };

    enum PrimitiveType
    {
        POINTS = 0,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_FAN,
        TRIANGLE_STRIP,

        Count,
    };

    enum MultisamplingType
    {
        SAMPLING_NONE,
        SAMPLING_2,
        SAMPLING_4
    };
}

#endif