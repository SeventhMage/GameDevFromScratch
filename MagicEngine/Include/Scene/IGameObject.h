#ifndef _IMAGIC_I_GAME_OBJECT_H_
#define _IMAGIC_I_GAME_OBJECT_H_

#include "Foundation/Object/IObject.h"
#include "Foundation/Object/IComponent.h"

namespace Magic
{
    class IGameObject : public IObject
    {
    public:
        virtual void AddComponent(IComponent *component) = 0;
        virtual void Update() = 0;
    };
}

#endif