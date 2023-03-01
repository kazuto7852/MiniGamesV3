#include "../../libOne/inc/libOne.h"
#include "GAME_BASE.h"
#include "TRANSITION_EFFECT.h"
#include "MAIN.h"

MAIN::MAIN()
{
	window(1920, 1080, full);
	//ゲームファクトリ生成
	GameFactory = new GAME_FACTORY(this);
	//スタート時のゲーム(メニュー)生成
	CurrentGameId = NextGameId = GAME_FACTORY::MENU_ID;
	GameBase = GameFactory->create(CurrentGameId);
	GameBase->create();
	//切り替え効果オブジェクト
	Transition = new TRANSITION_EFFECT;
}

MAIN::~MAIN()
{
	delete GameFactory;
	GameBase->destroy();
	delete GameBase;
	delete Transition;
}

void MAIN::run()
{
	initDeltaTime();
	//メインループ
	while (notQuit) {
		//メインプロシージャー
		setDeltaTime();
		GameBase->proc();
		Transition->proc();
		//GameBase->proc()内でゲームを切り替えていない
		if (CurrentGameId == NextGameId) {
			continue;
		}
		//GameBase->proc()内でゲームを切り替えた時ここに来る
		Transition->outStart();
		//画面切り替え効果終了後、次のゲームに切り替え
		if (Transition->outEndFlag()) {
			//現在のゲームを解放
			GameBase->destroy();
			delete GameBase;
			//次のゲームを生成
			CurrentGameId = NextGameId;
			GameBase = GameFactory->create(CurrentGameId);
			GameBase->create();
			//切り替え効果スタート
			Transition->inStart();
		}
	}
}

//MAINオブジェクト開始
void gmain()
{
	MAIN main;
	main.run();
}
