#ifndef _MAGIC_I_SHADER_PROGRAM_H_
#define _MAGIC_I_SHADER_PROGRAM_H_

#include "IShader.h"

namespace Magic
{
    class IShaderProgram
    {
    public:
        virtual ~IShaderProgram(){}
        virtual void Prepare() = 0;
        virtual void SetUniform(const char *name, const void *data, int size) = 0;
    };
}

#endif