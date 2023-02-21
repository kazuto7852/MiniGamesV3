#pragma once
#include "../MAIN/LEVEL.h"
class GAME02 :
    public LEVEL
{
public:
    GAME02(class MAIN* main) :LEVEL(main) {};
    ~GAME02() {};
    void create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

