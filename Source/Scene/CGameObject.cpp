#include "Scene/CGameObject.h"

namespace Magic
{
    CGameObject::CGameObject()
    {

    }

    CGameObject::~CGameObject()
    {

    }

    void CGameObject::AddComponent(IComponent *component)
    {
        _Components.push_back(component);
    }

}