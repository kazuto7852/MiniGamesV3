#pragma once
#include "GAME_FACTORY.h"
class MAIN
{
public:
	MAIN();
	~MAIN();
	void run();
	void setNextGameId(GAME_FACTORY::GAME_ID nextGameId) { 
		NextGameId = nextGameId; 
	}
	void backToMenu() {
		NextGameId = GAME_FACTORY::MENU_ID;
	}
private:
	//ゲームのシンプルファクトリオブジェクト
	class GAME_FACTORY* GameFactory = nullptr;
	//現在実行中のゲームID
	GAME_FACTORY::GAME_ID CurrentGameId;
	//次に実行予定のゲームID
	GAME_FACTORY::GAME_ID NextGameId;
	//実行中のゲームオブジェクト
	class GAME_BASE* GameBase = nullptr;
	//切り替え効果オブジェクト
	class TRANSITION_EFFECT* Transition = nullptr;
};
