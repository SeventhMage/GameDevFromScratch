#include "Graphic/Rendering/CShaderProgram.h"
#include <cstring>

namespace Magic
{
    void CShaderProgram::SetUniform(const char *name, const void *data, int size)
    {
        std::vector<float> value(size);
        memcpy(value.data(), data, size);
        _Uniforms[name] = value;
    }
}