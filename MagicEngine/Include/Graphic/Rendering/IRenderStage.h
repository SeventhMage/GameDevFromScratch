#ifndef _MAGIC_I_RENDER_STAGE_H_
#define _MAGIC_I_RENDER_STAGE_H_

#include "IRenderQueue.h"

namespace Magic
{
    class IRenderStage
    {
    public:
        virtual ~IRenderStage(){}
        virtual void AddRenderQueue(IRenderQueue *) = 0;
    };
}

#endif