#ifndef _WORLD_STATE_H_
#define _WORLD_STATE_H_

#include "GameState.h"

namespace Magic
{
    class WorldState : public GameState
    {
    public:
        virtual void Enter();
        virtual void Leave();
        virtual void Update();
    private:
    };
}

#endif