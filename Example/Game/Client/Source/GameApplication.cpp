#include <iostream>
#include "GameAppliaction.h"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Math.hpp"
#include "Foundation/Memory/Memory.h"
#include "Game.h"
#include "Scene/IGameScene.h"
#include "Scene/CCamera.h"


using namespace std;

namespace Magic
{
    IMPLEMENT_APP_INITIALIZE(GameApplication);
    IMPLEMENT_APP_TERMINATE(GameApplication);

    bool GameApplication::OnInitialize()
    { 
        cout << "GameApplication::OnInitialize" << endl;

        IGameScene *scene = SceneManager->LoadScene("GameScene.scene");
        assert(scene);
        ISceneNode *rootNode = scene->GetRootNode();
        IGameObject *camGo = rootNode->AddGameOject();
        // CameraTypeParam camParam;
        // camGo->AddComponent(NEW CCamera(camParam));

        IGameObject *heroGo = rootNode->AddGameOject();

        return true;
    }

    bool GameApplication::OnTerminate()
    {
        cout << "GameApplication::OnTerminate" << endl;
        SceneManager->UnloadScene();
        return true;
    }

    void GameApplication::OnUpdate()
    {
    }
}