#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

namespace Magic
{
    class GameState
    {
    public:
        enum StateID
        {
            Login = 0,
            World,

            Count,
        };
        GameState();
        
        virtual void Enter() {}
        virtual void Leave() {}
    };
}

#endif