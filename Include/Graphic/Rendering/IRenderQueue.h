#ifndef _MAGIC_IRENDER_QUEUE_H_
#define _MAGIC_IRENDER_QUEUE_H_

#include "IRenderInput.h"

namespace Magic
{
    class IRenderQueue
    {
    public:
        virtual ~IRenderQueue(){}
        virtual void AddRenderInput(IRenderInput *) = 0;
    };
}

#endif