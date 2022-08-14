#ifndef _MAGIC_C_SOFT_SHADER_PROGRAM_H_
#define _MAGIC_C_SOFT_SHADER_PROGRAM_H_

#include "Graphic/Rendering/CShaderProgram.h"
#include "Foundation/Math/Color.hpp"
#include "ISampler.h"

namespace Magic
{
    typedef void (*VProgram)(const void*, const void *, const void *, unsigned char*);
    typedef Color (*FProgram)(const void*, ISampler**, const void*);
    typedef std::map<std::string, std::vector<float>> UniformMap;
    class CSoftShaderProgram : public CShaderProgram
    {
    public:
        CSoftShaderProgram(VProgram vertProg, FProgram fragProg);
        VProgram GetVertexProgram() { return _VertexProgram; }
        FProgram GetFragmentProgram() { return _FragmentProgram; }

        UniformMap &GetUniforms() { return _Uniforms; }
    private:
        VProgram _VertexProgram;
        FProgram _FragmentProgram;
    };
}

#endif