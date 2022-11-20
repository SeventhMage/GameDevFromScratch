#ifndef _MAGIC_I_GAME_SCENE_H_
#define _MAGIC_I_GAME_SCENE_H_

#include "Terrain/ITerrain.h"
#include "ISkyBox.h"
#include "ISceneNode.h"
#include "ICamera.h"


namespace Magic
{
    class IGameScene
    {
    public:
        virtual ITerrain *GetTerrain() const = 0;
        virtual ISkyBox *GetSkyBox() const = 0;
        virtual ICamera *GetMainCamera() const = 0;

        virtual ISceneNode *GetRootNode() const = 0;

        virtual void Update() = 0;
        virtual void FixedUpdate() = 0;
        virtual void Render() = 0;
    };
}

#endif