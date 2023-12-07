#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME00 
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
        float Hue = 0, SpeedChangeHue = 0;
    };
}
