#pragma once
#include "../MAIN/GAME_BASE.h"
class GAME03 :
    public GAME_BASE
{
public:
    GAME03(class MAIN* main) :GAME_BASE(main) {};
    ~GAME03() {};
    int create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

