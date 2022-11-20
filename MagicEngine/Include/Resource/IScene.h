#ifndef _MAGIC_I_SCENE_H_
#define _MAGIC_I_SCENE_H_

#include "IResource.h"

namespace Magic
{
    class IScene : public IResource
    {
    public:
        virtual Type GetType() const {return SCENE; }
    };
}

#endif