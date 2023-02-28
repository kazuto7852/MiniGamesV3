#pragma once
#include "../MAIN/GAME_BASE.h"
class GAME02 :
    public GAME_BASE
{
public:
    GAME02(class MAIN* main) :GAME_BASE(main) {};
    ~GAME02() {};
    int create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

