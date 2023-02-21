#pragma once
#include "../MAIN/LEVEL.h"
class GAME03 :
    public LEVEL
{
public:
    GAME03(class MAIN* main) :LEVEL(main) {};
    ~GAME03() {};
    void create();
    void proc();
    void destroy();
private:
    float Px = 0, Py = 0, Radius = 0;
};

