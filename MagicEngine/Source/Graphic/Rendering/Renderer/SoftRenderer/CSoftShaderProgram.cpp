#include "Graphic/Rendering/CSoftShaderProgram.h"

namespace Magic
{
    CSoftShaderProgram::CSoftShaderProgram(VProgram vertProg, FProgram fragProg)
        : _VertexProgram(vertProg), _FragmentProgram(fragProg)
    {
    }

}