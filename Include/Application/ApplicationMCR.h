#ifndef _MAGIC_APPLICATION_MCR_H_
#define _MAGIC_APPLICATION_MCR_H_

#include "Foundation/System/MainMCR.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
#define IMPLEMENT_APP_INITIALIZE(classname) \
    IMPLEMENT_INITIALIZE(classname);        \
    void classname::Initialize()            \
    {                                       \
        TheApp = NEW classname;       \
    }
}

#endif