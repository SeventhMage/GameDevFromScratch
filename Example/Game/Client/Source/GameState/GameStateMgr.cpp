#include "GameStateMgr.h"
#include "Foundation/Memory/Memory.h"
#include "GameState/WorldState.h"
#include "GameState/LoginState.h"

namespace Magic
{
    GameStateMgr::GameStateMgr()
    {
        _GameStates[GameState::StateID::World] = NEW WorldState();
        _GameStates[GameState::StateID::Login] = NEW LoginState();
    }

    GameStateMgr::~GameStateMgr()
    {
        for (int i = 0; i < GameState::StateID::Count; ++i)
        {
            SAFE_DELETE(_GameStates[i]);
        }
    }

    void GameStateMgr::EnterState(GameState::StateID stateId)
    {
        _GameStateStack.push_back(stateId);
    }

    void GameStateMgr::LeaveState()
    {
        int size = _GameStateStack.size();
        if (size > 1)
        {
            auto curId = _GameStateStack[size - 1];
            _GameStates[curId]->Leave();
            _GameStateStack.pop_back();
            auto nextId = _GameStateStack[size - 1];
            _GameStates[nextId]->Enter();
        }
    }

    void GameStateMgr::Update()
    {
        if (_GameStateStack.size() > 0)
        {
            int curStateId = _GameStateStack[_GameStateStack.size() - 1];
            _GameStates[curStateId]->Update();
        }
    }
}