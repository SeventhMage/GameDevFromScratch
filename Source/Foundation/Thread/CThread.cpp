#include "Foundation/Thread/CThread.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    #if false
    CThread::CThread()
        : _Thread(nullptr)
    {
    }
    CThread::~CThread()
    {
        SAFE_DELETE(_Thread);
    }

    void CThread::Start()
    {
        _Thread = NEW std::thread(&CThread::Running, this);
        _Thread->detach();
    }

    void CThread::Stop()
    {
        SAFE_DELETE(_Thread);
    }
    #endif
}