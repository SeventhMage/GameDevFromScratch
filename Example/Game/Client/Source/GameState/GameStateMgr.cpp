#include "GameStateMgr.h"

namespace Magic
{
    GameStateMgr::GameStateMgr()
    {

    }

    GameStateMgr::~GameStateMgr()
    {

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
}