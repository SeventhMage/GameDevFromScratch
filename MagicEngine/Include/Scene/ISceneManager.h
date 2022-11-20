#ifndef _MAGIC_I_SCENE_MANAGER_H_
#define _MAGIC_I_SCENE_MANAGER_H_

#include "IGameScene.h"

namespace Magic
{
    class ISceneManager
    {
    public:
        virtual IGameScene *LoadScene(const char *path) = 0;
        virtual void UnloadScene() = 0;
        virtual bool SaveScene() = 0;
        virtual IGameScene *GetActiveScene() const = 0;
        virtual void Update() = 0;
    };
}

#endif