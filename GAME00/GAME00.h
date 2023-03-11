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
        //ÉVÅ[ÉìëJà⁄
        enum STATE { TITLE, PLAY, CLEAR, OVER };
        STATE State = TITLE;
        void Title();
        void Init();
        void Play();
        void Clear();
        bool ClearFlag = false;
        //â~
        float CircleRadius = 0;
        float CircleX = 0, CircleY = 0;
        float CircleVx = 0, CircleVy = 0;
        //îöî≠
        int ExplosionImg = 0;
        int ExplosionSnd = 0;
    };
}
