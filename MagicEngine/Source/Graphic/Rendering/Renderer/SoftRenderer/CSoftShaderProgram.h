#ifndef _MAGIC_C_SOFT_SHADER_PROGRAM_H_
#define _MAGIC_C_SOFT_SHADER_PROGRAM_H_

#include "Graphic/Rendering/CShaderProgram.h"
#include "Graphic/Rendering/ISampler.h"
#include "Foundation/Math/Color.hpp"

using namespace std;

namespace Magic
{
    typedef void (*VProgram)(const void*, const void *, const void *, unsigned char*);
    typedef Color (*FProgram)(const void*, ISampler**, const void*);
    typedef map<string, vector<float>> UniformMap;
    class CSoftShaderProgram : public CShaderProgram
    {
    public:
        CSoftShaderProgram(VProgram vertProg, FProgram fragProg);
        CSoftShaderProgram(const char *vertexShader, const char *fragShader);
        VProgram GetVertexProgram() { return _VertexProgram; }
        FProgram GetFragmentProgram() { return _FragmentProgram; }

        UniformMap &GetUniforms() { return _Uniforms; }
    private:
        VProgram _VertexProgram;
        FProgram _FragmentProgram;
    };
}

#endif