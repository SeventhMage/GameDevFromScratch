#ifndef _MAGIC_C_RENDER_THREAD_H_
#define _MAGIC_C_RENDER_THREAD_H_

#include "Foundation/Thread/CThread.h"
#include "IRenderer.h"

namespace Magic
{
    class CRenderThread //: public CThread
    {
    public:
        virtual void Running();
    private:
        IRenderer *Renderer;
    };
}

#endif