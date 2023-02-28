#pragma once
#include "../MAIN/GAME_BASE.h"
class GAME01 :
    public GAME_BASE
{
public:
    GAME01(class MAIN* main) :GAME_BASE(main) {};
    ~GAME01() {};
    int create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
    float Hue = 0, SpeedChangeHue = 0;
};

