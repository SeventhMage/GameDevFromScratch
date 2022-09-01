#ifndef _MAGIC_C_TEXTURE_2D_H_
#define _MAGIC_C_TEXTURE_2D_H_

#include "Graphic/Rendering/ITexture.h"
#include "Foundation/Math/Color.hpp"
#include "Foundation/Math/Vector2.hpp"
#include "Resource/IImage.h"


namespace Magic
{
    class CSoftTexture2D : public ITexture
    {
    public:
        CSoftTexture2D(const char *fullName);
        Color GetPixel(const Vector2f &uv) const;
        Color GetPixel(int x, int y) const;
    private:
        IImage *_Image;
    };
}

#endif