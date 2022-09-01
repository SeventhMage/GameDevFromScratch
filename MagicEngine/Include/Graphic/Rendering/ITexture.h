#ifndef _MAGIC_I_TEXTURE_H_
#define _MAGIC_I_TEXTURE_H_

namespace Magic
{
    class ITexture
    {
    public:
        enum Format
        {
            ARGB32,
        };
        virtual ~ITexture(){}
        virtual void Prepare() {}
    };
}

#endif