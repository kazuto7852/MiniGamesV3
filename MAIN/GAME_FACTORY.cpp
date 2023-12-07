#include "../GAME00/GAME00.h"
#include "../GAME01/GAME01.h"
#include "../GAME02/GAME02.h"
#include "../GAME03/GAME03.h"
#include "../GAME04/GAME04.h"
#include "../GAME05/GAME05.h"
#include "../GAME06/GAME06.h"
#include "../GAME07/GAME07.h"
#include "../GAME08/GAME08.h"
#include "../GAME09/GAME09.h"
#include "../GAME10/GAME10.h"
#include "../GAME11/GAME11.h"
#include "../GAME12/GAME12.h"
#include "../GAME13/GAME13.h"
#include "../GAME14/GAME14.h"
#include "../GAME15/GAME15.h"
#include "../MENU/MENU.h"
#include "MAIN.h"
#include "GAME_FACTORY.h"

GAME_FACTORY::GAME_FACTORY(MAIN* main):Main(main){}

GAME_FACTORY::~GAME_FACTORY(){Main = nullptr;}

GAME_BASE* GAME_FACTORY::create(GAME_ID id)
{
	if (id == GAME00_ID)return new GAME00::GAME(Main);
	if (id == GAME01_ID)return new GAME01::GAME(Main);
	if (id == GAME02_ID)return new GAME02::GAME(Main);
	if (id == GAME03_ID)return new GAME03::GAME(Main);
	if (id == GAME04_ID)return new GAME04::GAME(Main);
	if (id == GAME05_ID)return new GAME05::GAME(Main);
	if (id == GAME06_ID)return new GAME06::GAME(Main);
	if (id == GAME07_ID)return new GAME07::GAME(Main);
	if (id == GAME08_ID)return new GAME08::GAME(Main);
	if (id == GAME09_ID)return new GAME09::GAME(Main);
	if (id == GAME10_ID)return new GAME10::GAME(Main);
	if (id == GAME11_ID)return new GAME11::GAME(Main);
	if (id == GAME12_ID)return new GAME12::GAME(Main);
	if (id == GAME13_ID)return new GAME13::GAME(Main);
	if (id == GAME14_ID)return new GAME14::GAME(Main);
	if (id == GAME15_ID)return new GAME15::GAME(Main);
	if (id == MENU_ID)return new MENU(Main);
	return nullptr;
}
