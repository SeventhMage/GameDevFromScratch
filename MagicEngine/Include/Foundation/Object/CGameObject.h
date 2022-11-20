#ifndef _MAGIC_C_GAME_OBJECT_H_
#define _MAGIC_C_GAME_OBJECT_H_

#include <vector>

#include "CObject.h"
#include "IComponent.h"

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