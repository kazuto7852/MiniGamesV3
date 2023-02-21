#pragma once
class LEVEL_FACTORY
{
public:
	enum LEVEL_ID {
		GAME00_ID,
		GAME01_ID,
		GAME02_ID,
		GAME03_ID,
		MENU_ID=100,
	};
	LEVEL_FACTORY(class MAIN* main);
	~LEVEL_FACTORY();
	class LEVEL* create(LEVEL_ID id);
private:
	class MAIN* Main;
};