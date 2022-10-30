#ifndef _MAGIC_I_IMAGE_H_
#define _MAGIC_I_IMAGE_H_

#include "IResource.h"

namespace Magic
{

    class IImage : public IResource
    {
    public:
        enum Format
        {
            ALPHA,
            RGB,
            RGBA,
            RGB16F,
            BGR,
            BGRA,
            LUMINANCE,
        };

        virtual Type GetType() const { return IMAGE; }
		virtual unsigned char *GetData() const = 0;
		virtual Format GetFormat() const = 0;
		virtual unsigned long GetImageSize() const = 0;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
    };
}

#endif