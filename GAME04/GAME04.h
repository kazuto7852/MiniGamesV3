#pragma once
#include "../MAIN/LEVEL.h"
class GAME04 :
    public LEVEL
{
public:
    GAME04(class MAIN* main) :LEVEL(main) {};
    ~GAME04() {};
    int create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

