#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include"LEVEL.h"
LEVEL::LEVEL(class MAIN* main) 
	:Main(main) 
{
}
LEVEL::~LEVEL()
{
	refreshCntnr();
	releaseAllSound();
}