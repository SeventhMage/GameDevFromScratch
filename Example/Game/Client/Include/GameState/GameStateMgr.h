#ifndef _GAME_STATE_MGR_H_
#define _GAME_STATE_MGR_H_

#include "Foundation/Utils/Singleton.hpp"
#include "GameState.h"

#include <vector>

namespace Magic
{
    class GameStateMgr : public Singleton<GameStateMgr>
    {
    public:
        void EnterState(GameState::StateID stateId);
        void LeaveState();
        void Update();
    private:
        friend class Singleton<GameStateMgr>;
        GameStateMgr();
        ~GameStateMgr();
        std::vector<GameState::StateID> _GameStateStack;
        GameState *_GameStates[GameState::StateID::Count];
    };
}

#endif