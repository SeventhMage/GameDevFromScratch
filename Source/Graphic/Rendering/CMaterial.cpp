#include "Graphic/Rendering/CMaterial.h"

namespace Magic
{

    CMaterial::CMaterial()
    {
    }
    CMaterial::~CMaterial()
    {
    }
    void CMaterial::SetShader(IShader *shader, EShader slot)
    {
        _Shaders[slot] = shader;
    }
}