#ifndef _MAGIC_GAME__H_
#define _MAGIC_GAME__H_

#include "Foundation/Utils/Singleton.hpp"

namespace Magic
{
    class Game : public Singleton<Game>
    {
    public:
        Game();
        ~Game();
        void Initalize();
        void Terminate();
        void Update();

    };
}

#endif