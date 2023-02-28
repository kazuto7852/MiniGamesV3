#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include"GAME_BASE.h"
GAME_BASE::GAME_BASE(class MAIN* main) 
	:Main(main) 
{
	//無音ファイルを再生する。
	//これをしておかないとなぜか、１発目の再生が遅延する。
	playSound(loadSound("../main/assets/silence.wav"));
}
GAME_BASE::~GAME_BASE()
{
	refreshCntnr();
	releaseAllSound();
}