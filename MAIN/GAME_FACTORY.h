#pragma once
class GAME_FACTORY
{
public:
	enum GAME_ID {
		GAME00_ID,
		GAME01_ID,
		GAME02_ID,
		GAME03_ID,
		GAME04_ID,
		GAME05_ID,
		MENU_ID=100,
	};
	GAME_FACTORY(class MAIN* main);
	~GAME_FACTORY();
	class GAME_BASE* create(GAME_ID id);
private:
	class MAIN* Main;
};