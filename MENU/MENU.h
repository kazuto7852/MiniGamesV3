#pragma once
#include <string>
#include "../MAIN/LEVEL.h"
class MENU :
    public LEVEL
{
public:
    MENU(class MAIN* main) :LEVEL(main) {};
    ~MENU() {};
    int create();
    void proc();
    void destroy();
private:
    //レベルインデックスの位置をマウスで変える
    void ChangePosition();
    char* Indices;
    int NumIndices;
    int IndexMouseHolding;
    int IndexMouseOver;
    std::string* Titles;
    void Draw();
    int Rows, Cols;
    float TileH, TileW;
    float OfstX, OfstY;
    float DivHue;
    float SizeText;
};

