#include "../GAME00/GAME00.h"
#include "../GAME01/GAME01.h"
#include "../GAME02/GAME02.h"
#include "../GAME03/GAME03.h"
#include "../GAME04/GAME04.h"
#include "../GAME05/GAME05.h"
#include "../MENU/MENU.h"
#include "MAIN.h"
#include "LEVEL_FACTORY.h"

LEVEL_FACTORY::LEVEL_FACTORY(MAIN* main):Main(main){}

LEVEL_FACTORY::~LEVEL_FACTORY(){Main = nullptr;}

LEVEL* LEVEL_FACTORY::create(LEVEL_ID id)
{
	if (id == GAME00_ID)return new GAME00(Main);
	if (id == GAME01_ID)return new GAME01(Main);
	if (id == GAME02_ID)return new GAME02(Main);
	if (id == GAME03_ID)return new GAME03(Main);
	if (id == GAME04_ID)return new GAME04(Main);
	if (id == GAME05_ID)return new GAME05(Main);
	if (id == MENU_ID)return new MENU(Main);
	return nullptr;
}
