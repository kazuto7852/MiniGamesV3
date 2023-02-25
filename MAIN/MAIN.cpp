#include "../../libOne/inc/libOne.h"
#include "LEVEL.h"
#include "TRANSITION_EFFECT.h"
#include "MAIN.h"

MAIN::MAIN()
{
	window(1920, 1080, full);
	//レベルファクトリ生成
	LevelFactory = new LEVEL_FACTORY(this);
	//スタート時のレベルをつくる
	CurrentLevelId = NextLevelId = LEVEL_FACTORY::MENU_ID;
	Level = LevelFactory->create(CurrentLevelId);
	Level->create();
	//切り替え効果オブジェクト
	Transition = new TRANSITION_EFFECT;
}

MAIN::~MAIN()
{
	delete LevelFactory;
	Level->destroy();
	delete Level;
	delete Transition;
}

void MAIN::run()
{
	initDeltaTime();
	//メインループ
	while (notQuit) {

		setDeltaTime();
		Level->proc();
		Transition->proc();

		//Level->proc()内でレベルを切り替えていない
		if (CurrentLevelId == NextLevelId) {
			continue;
		}
		//Level->proc()内でレベルを切り替えた時ここに来る
		Transition->outStart();
		//画面切り替え効果終了後、Level切り替え
		if (Transition->outEndFlag()) {
			//現在のレベルを解放
			Level->destroy();
			delete Level;
			//次のレベルを生成
			CurrentLevelId = NextLevelId;
			Level = LevelFactory->create(CurrentLevelId);
			Level->create();
			//切り替え効果スタート
			Transition->inStart();
		}
	}
}

void gmain()
{
	MAIN main;
	main.run();
}
