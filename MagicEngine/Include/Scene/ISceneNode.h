#ifndef _MAGIC_I_SCENE_NODE_H_
#define _MAGIC_I_SCENE_NODE_H_

#include "IGameObject.h"
#include <vector>

namespace Magic
{
    class ISceneNode
    {
    public:
        virtual void AddChildNode(ISceneNode *) = 0;
        virtual ISceneNode *CreateChildNode() = 0;
        virtual IGameObject *AddGameOject() = 0;
        virtual void RemoveGameObject(IGameObject *) = 0;
        virtual std::vector<IGameObject *> GetGameObjects() const = 0;
        virtual void Update() = 0;
    };
}

#endif