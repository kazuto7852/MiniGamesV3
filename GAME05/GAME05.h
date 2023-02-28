#pragma once
#include "../MAIN/GAME_BASE.h"
class GAME05 :
    public GAME_BASE
{
public:
    GAME05(class MAIN* main) :GAME_BASE(main) {};
    ~GAME05() {};
    int create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

