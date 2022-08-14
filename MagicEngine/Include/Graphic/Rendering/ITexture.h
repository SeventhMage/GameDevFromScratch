#ifndef _MAGIC_I_TEXTURE_H_
#define _MAGIC_I_TEXTURE_H_

namespace Magic
{
    class ITexture
    {
    public:
        virtual ~ITexture(){}
        virtual void Prepare() = 0;
    };
}

#endif