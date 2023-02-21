#pragma once
#include "../MAIN/LEVEL.h"
class MENU :
    public LEVEL
{
public:
    MENU(class MAIN* main) :LEVEL(main) {};
    ~MENU() {};
    void create();
    void proc();
    void destroy();
private:
    int Rows, Cols;
    float TileH, TileW;
    float OfstX, OfstY;
    float DivHue;
};

