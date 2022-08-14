#ifndef _MAGIC_C_SHADER_PROGRAM_H_
#define _MAGIC_C_SHADER_PROGRAM_H_

#include "Graphic/Rendering/IShaderProgram.h"
#include <vector>
#include <map>
#include <string>

namespace Magic
{
    class CShaderProgram : public IShaderProgram
    {
    public:
        virtual void Prepare() {}
        virtual void SetUniform(const char *name, const void *data, int size);
    protected:
        std::map<std::string, std::vector<float>> _Uniforms;
    };
}

#endif