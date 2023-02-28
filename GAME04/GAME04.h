#pragma once
#include "../MAIN/GAME_BASE.h"
class GAME04 :
    public GAME_BASE
{
public:
    GAME04(class MAIN* main) :GAME_BASE(main) {};
    ~GAME04() {};
    int create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

