#pragma once
#include "../MAIN/LEVEL.h"
class GAME05 :
    public LEVEL
{
public:
    GAME05(class MAIN* main) :LEVEL(main) {};
    ~GAME05() {};
    void create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

