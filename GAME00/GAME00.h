#pragma once
#include "../MAIN/LEVEL.h"
class GAME00 :
    public LEVEL
{
public:
    GAME00(class MAIN* main) :LEVEL(main) {};
    ~GAME00() {};
    int create();
    void proc();
    void destroy();
private:
    //ÉVÅ[ÉìëJà⁄
    enum STATE{ TITLE,PLAY,CLEAR,OVER };
    STATE State = TITLE;
    void Title();
    void Init();
    void Play();
    void Clear();
    //â~
    float CircleX = 0, CircleY = 0, CircleRadius = 0;
    float CircleVy = 0;
    //îöî≠
    int ExplosionImg = 0;
    int ExplosionSnd = 0;
};

