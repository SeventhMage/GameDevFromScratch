#ifndef _MAGIC_C_GAME_OBJECT_H_
#define _MAGIC_C_GAME_OBJECT_H_

#include <vector>

#include "Foundation/Object/CObject.h"
#include "Foundation/Object/IComponent.h"

namespace Magic
{
    class CGameObject : public CObject
    {
    public:
        CGameObject();
        ~CGameObject();
        void AddComponent(IComponent *component);
    private:
        std::vector<IComponent *> _Components;
    };

}

#endif