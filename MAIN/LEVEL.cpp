#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include"LEVEL.h"
LEVEL::LEVEL(class MAIN* main) 
	:Main(main) 
{
	//無音ファイルを再生する。
	//これをしておかないとなぜか、１発目の再生が遅延する。
	playSound(loadSound("../main/assets/silence.wav"));
}
LEVEL::~LEVEL()
{
	refreshCntnr();
	releaseAllSound();
}