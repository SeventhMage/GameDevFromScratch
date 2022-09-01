#include "CSoftTexture2D.h"
#include "Resource/CTGAImage.h"
#include "Resource/CResourceMgr.h"

namespace Magic
{
    CSoftTexture2D::CSoftTexture2D(const char *fullName)
    {
        _Image = (IImage *)CResourceMgr::Instance()->LoadResource(fullName);
    }

    Color CSoftTexture2D::GetPixel(const Vector2f &uv)const
    {
        int width = _Image->GetWidth();
        int height = _Image->GetHeight();
        return GetPixel((int)(uv.x * (width - 1)), (int)(uv.y * (height - 1)));
    }
    Color CSoftTexture2D::GetPixel(int x, int y)const
    {
        if (_Image->GetFormat() == IImage::BGR)
        {
            int width = _Image->GetWidth();
            int height = _Image->GetHeight();
            if (x >= 0 && x < width && y >=0 && y < height)
            {
                unsigned char *data = (unsigned char*)_Image->GetData();
                unsigned char *addr = data + width * y * 3 + x * 3;
                float inv = 1.f / 255.f;
                return Color(1.f, *(addr + 2) * inv, *(addr + 1) * inv, (*addr) *inv );
            }
        }
        return Color();
    }
}