#pragma once
#include <string>
#include <memory>
#include "../MAIN/GAME_BASE.h"
class MENU :
    public GAME_BASE
{
public:
    MENU(class MAIN* main) :GAME_BASE(main) {};
    ~MENU() {};
    int create();
    void proc();
    void destroy();
private:
    //ファイル読み込み create()から呼び出される
    void LoadGameIndices();
    void LoadTitleNames();
    //ゲームインデックスの位置をマウスで変える proc()から呼び出される
    void ChangeGameIndices();
    char* GameIndices=0; 
    int NumGameIndices=0;
    int TileIndexMouseHolding=0;
    int TileIndexMouseOver=0;
    //メニュー描画 procから呼び出される
    void Draw();
    int Rows=0, Cols=0;
    float TileH=0, TileW=0;
    float OfstX=0, OfstY=0;
    float DivHue=0;
    float SizeText=0;
    std::string* Titles=0;
};

