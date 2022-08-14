#ifndef _MAGIC_MAIN_MCR_H_
#define _MAGIC_MAIN_MCR_H_

#include "CMain.h"

namespace Magic
{
#define DECLARE_INITIALIZE            \
public:                               \
    static bool RegisterInitialize(); \
    static void Initialize();         \
                                      \
private:                              \
    static bool _bInitializeRegistered

#define IMPLEMENT_INITIALIZE(classname)                   \
    bool classname::_bInitializeRegistered = false;       \
    bool classname::RegisterInitialize()                  \
    {                                                     \
        if (!_bInitializeRegistered)                      \
        {                                                 \
            CMain::AddInitializer(classname::Initialize); \
            _bInitializeRegistered = true;                \
        }                                                 \
        return _bInitializeRegistered;                    \
    }
}

#define REGISTER_INITIALIZE(classname)              \
    static bool bInitializeRegistered_##classname = \
        classname::RegisterInitialize()

#endif