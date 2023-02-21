#pragma once
#include "LEVEL_FACTORY.h"
class MAIN
{
public:
	MAIN();
	~MAIN();
	void run();
	void setNextLevelId(LEVEL_FACTORY::LEVEL_ID nextLevelId) { 
		NextLevelId = nextLevelId; 
	}
	void backToMenu() {
		NextLevelId = LEVEL_FACTORY::MENU_ID;
	}
private:
	//レベルのシンプルファクトリ
	class LEVEL_FACTORY* LevelFactory = nullptr;
	//現在実行中のレベルID
	LEVEL_FACTORY::LEVEL_ID CurrentLevelId;
	//次に実行予定のレベルID
	LEVEL_FACTORY::LEVEL_ID NextLevelId;
	//実行中のレベル
	class LEVEL* Level = nullptr;
	//切り替え効果
	class TRANSITION_EFFECT* Transition = nullptr;
};
