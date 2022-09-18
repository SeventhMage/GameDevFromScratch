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

    enum RenderState
    {
        SCISSOR_TEST = 0x00000001,
        STENCIL_TEST = 0x00000001 << 1,
        DEPTH_TEST = 0x00000001 << 2,
        DEPTH_WRITE = 0x00000001 << 3,
        ALPHA_TEST = 0x00000001 << 4,

        DEFAULT = DEPTH_TEST | DEPTH_WRITE,
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
        NEVER = 0,
        LESS,
        GREATER,
        EQUAL,
        NEQUAL,
        LEQUAL,
        GEQUAL,
        ALWAYS,
        
        CF_COUNT,
    };

    enum TestState
    {
        STENCIL_FAIL,
        DEPTH_FAIL,
        STENCIL_DEPTH_PASS,
    };

    enum StencilOperation
    {
        KEEP = 0,
        MAKE_ZERO,
        REPLACE,
        INCREMENT,
        DECREMENT,
        INVERT,

        SO_COUNT,
    };

    enum BlendFactor
    {
        ONE, 
        ZERO,
        SRC_COLOR,
        SRC_ALPHA,
        DST_COLOR,
        DST_ALPHA,
        ONE_MINUS_SRC_COLOR,
        ONE_MINUS_SRC_ALPHA,
        ONE_MINUS_DST_COLOR,
        ONE_MINUS_DST_ALPHA,

        BF_COUNT,
    };

    enum BlendOperation
    {
        ADD,
        SUB,
        REVSUB,

        BO_COUNT,
    };

    enum PrimitiveType
    {
        POINTS = 0,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_FAN,
        TRIANGLE_STRIP,
        PT_COUNT,
    };

    enum MultisamplingType
    {
        SAMPLING_NONE,
        SAMPLING_2,
        SAMPLING_4
    };
}

#endif