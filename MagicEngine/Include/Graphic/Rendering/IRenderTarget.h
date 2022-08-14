#ifndef _MAGIC_RENDER_TARGET_H_
#define _MAGIC_RENDER_TARGET_H_

namespace Magic
{
    class IRenderTarget
    {
    public:
        virtual ~IRenderTarget(){}
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

    };
}

#endif