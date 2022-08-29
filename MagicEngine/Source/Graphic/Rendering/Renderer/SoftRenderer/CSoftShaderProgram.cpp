#include "CSoftShaderProgram.h"
#include "Graphic/Rendering/CSoftProgram.h"

#include <iostream>

namespace Magic
{
    CSoftShaderProgram::CSoftShaderProgram(VProgram vertProg, FProgram fragProg)
        : _VertexProgram(vertProg), _FragmentProgram(fragProg)
    {
    }

    CSoftShaderProgram::CSoftShaderProgram(const char *vertexShader, const char *fragShader)
    {
        _VertexProgram = CSoftProgram::GetVProgram(vertexShader);
        _FragmentProgram = CSoftProgram::GetFProgram(fragShader);

        std::cout << _VertexProgram << " " << _FragmentProgram << " " << vertexShader << " " << fragShader << std::endl; 
    }
}