#include "Game.h"
#include "GameState/GameStateMgr.h"

namespace Magic
{
    Game::Game()
    {

    }
    Game::~Game()
    {

    }

    void Game::Initalize()
    {
        //GameStateMgr::Instance()->EnterState(GameState::StateID::World);       
    }

    void Game::Terminate()
    {

    }

    void Game::Update()
    {
        //GameStateMgr::Instance()->Update();
    }
}