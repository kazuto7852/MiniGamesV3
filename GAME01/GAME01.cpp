#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"

int GAME01::create()
{
	//ここでは主に画像と音データを読み込む

	//初期値設定はInit()関数などを作ってそこで行ったほうが良い。
	//シンプルなゲームなら次のように、ここで行ってもよい。
	Px = width / 2;
	Py = height / 2;
	Radius = 200;

	Hue = 0;
	SpeedChangeHue = 60;

	return 0;
}

void GAME01::destroy()
{
	//create()でnewした場合はここでdeleteすること
}

void GAME01::proc()
{
	//ここはメインループから呼び出されている!!!!!

	//更新--------------------------------------------------
	Hue += SpeedChangeHue * delta;
	//描画--------------------------------------------------
	colorMode(HSV);
	angleMode(DEGREES);//for HUE
	clear(255, 0, 255);
	//円
	strokeWeight(50);
	stroke(0);
	fill(Hue, 255, 255);
	circle(Px, Py, Radius * 2);
	//テキスト情報
	fill(0);
	textSize(100);
	text("Enterでメニューに戻る", 0, height);
	print(1);
	//メニューに戻る------------------------------------------
	if (isTrigger(KEY_ENTER)) {
		main()->backToMenu();
	}
}

