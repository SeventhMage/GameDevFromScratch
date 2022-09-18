#ifndef _MAGIC__SOFT_SHADER_MCR_H_
#define _MAGIC__SOFT_SHADER_MCR_H_

#include "CSoftProgram.h"
#include "Foundation/System/CMain.h"

namespace Magic
{
#define IMPLEMENT_VPROGRAM(program)                         \
    static bool bVInitializeRegistered_##program = false;   \
    static void program##Initialize()                       \
    {                                                       \
        CSoftProgram::RegisterVProgram(#program, &program); \
    }                                                       \
    bool program##Register()                                \
    {                                                       \
        if (!bVInitializeRegistered_##program)              \
        {                                                   \
            CMain::AddInitializer(&program##Initialize);    \
        }                                                   \
        return bVInitializeRegistered_##program;            \
    }

#define REGISTER_VPROGRAM(program) \
    IMPLEMENT_VPROGRAM(program);   \
    static bool bInitializeRegistered_##program = program##Register()

#define IMPLEMENT_FPROGRAM(program)                         \
    static bool bVInitializeRegistered_##program = false;                \
    static void program##Initialize()                                    \
    {                                                                    \
        CSoftProgram::RegisterFProgram(#program, &program); \
    }                                                                    \
    bool program##Register()                                             \
    {                                                                    \
        if (!bVInitializeRegistered_##program)                           \
        {                                                                \
            CMain::AddInitializer(&program##Initialize);                 \
        }                                                                \
        return bVInitializeRegistered_##program;                         \
    }

#define REGISTER_FPROGRAM(program) \
    IMPLEMENT_FPROGRAM(program);   \
    static bool bInitializeRegistered_##program = program##Register()

}

#define V2F_COLOR(datas) *((Color *)datas)
#define V2F_UV(datas) *((Vector2f *)((char *)datas + sizeof(Color)))
#define V2F_NORMAL(datas) *((Color *)(char *)datas + sizeof(Color) + sizeof(Vector2f)))

#endif