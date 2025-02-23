#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME14
{
    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
    private:
        float Px = 0, Py = 0, Radius = 0;
    };
}
