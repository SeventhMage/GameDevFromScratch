#include "CSampler.h"

namespace Magic
{
    CSampler::CSampler()
    :_pTexture(nullptr)
    {

    }
    Color CSampler::Sample(const Vector2f &uv) 
    {
        if (_pTexture)
            return _pTexture->GetPixel(uv);
        return Color();
    }

    void CSampler::SetTexture(CSoftTexture2D *texture)
    {
        _pTexture = texture;
    }
}