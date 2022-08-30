#include "CSampler.h"

namespace Magic
{
    CSampler::CSampler()
    :_pTexture(nullptr)
    {

    }
    Color CSampler::Sample(const Vector2f &uv) 
    {

    }

    void CSampler::SetTexture(ITexture *texture)
    {
        _pTexture = texture;
    }
}