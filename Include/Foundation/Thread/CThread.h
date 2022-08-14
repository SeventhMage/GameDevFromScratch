#ifndef _MAGIC_C_THREAD_H_
#define _MAGIC_C_THREAD_H_

#if false

#include <thread>

namespace Magic
{
    class CThread
    {
    public:
        CThread();
        virtual ~CThread();
        virtual void Running() = 0;

        void Start();
        void Stop();
    private:
        std::thread *_Thread;
    };
}

#endif

#endif