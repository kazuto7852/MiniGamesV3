#pragma once
#include "../MAIN/LEVEL.h"
class GAME01 :
    public LEVEL
{
public:
    GAME01(class MAIN* main) :LEVEL(main) {};
    ~GAME01() {};
    int create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
    float Hue = 0, SpeedChangeHue = 0;
};

