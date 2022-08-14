#include "Foundation/Object/CObject.h"

namespace Magic
{
    static int sInstanceID = 0;
    int CObject::GetInstanceID()
    {
        return ++sInstanceID;
    }
}