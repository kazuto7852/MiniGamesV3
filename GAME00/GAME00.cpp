#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include "../../libOne/inc/window.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/rand.h"
#include "../MAIN/MAIN.h"
#include "GAME00.h"

int GAME00::create()
{
	State = TITLE;
	ExplosionImg = loadImage("..\\main\\assets\\game00\\explosion.png");
	ExplosionSnd = loadSound("..\\main\\assets\\game00\\bomb.wav");

	return 0;
}

void GAME00::destroy()
{
}

void GAME00::proc()
{
	//シーン切り替え
	if      (State == TITLE)Title();
	else if (State == PLAY )Play();
	else if (State == CLEAR)Clear();
}

void GAME00::Title()
{
	//描画--------------------------------------------------
	clear(60, 60, 60);
	//テキスト情報
	fill(255, 255, 255);
	textSize(80);
	print("Title：落ちてくる円をクリックするゲーム");
	print("　クリックでゲームスタート");
	print("  Enterでメニューに戻る");
	//シーン切り替え-----------------------------------------
	if (isTrigger(MOUSE_LBUTTON)) {
		Init();
		State = PLAY;
		return;
	}
	//メニューに戻る-----------------------------------------
	if (isTrigger(KEY_ENTER)) {
		main()->backToMenu();
	}
}

void GAME00::Init()
{
	CircleRadius = 50;
	CircleX = random() % 1000 + 500.0f;
	CircleY = -CircleRadius;
	CircleVy = 800;
}

void GAME00::Play()
{
	//更新--------------------------------------------------
	CircleY += CircleVy * delta;
	if (CircleY > height + CircleRadius) {
		CircleX = random() % 1000 + 500.0f;
		CircleY = -CircleRadius;
	}
	//描画--------------------------------------------------
	clear(0, 60, 0);
	//円
	fill(255);
	circle(CircleX, CircleY, CircleRadius * 2);
	//テキスト情報
	fill(255, 255, 255);
	print("Play");
	print("　円をクリックするとGame Clear");
	//シーン切り替え-----------------------------------------
	if (isTrigger(MOUSE_LBUTTON)) {
		float dx = CircleX - mouseX;
		float dy = CircleY - mouseY;
		if (dx * dx + dy * dy < CircleRadius * CircleRadius) {
			playSound(ExplosionSnd);
			State = CLEAR;
		}
	}
}

void GAME00::Clear()
{
	//描画--------------------------------------------------
	clear(0,0, 255);
	//爆発画像
	rectMode(CENTER);
	image(ExplosionImg, CircleX, CircleY);
	//テキスト情報
	fill(255, 255, 255);
	print("Game Clear");
	print("　クリックでタイトルに戻る");
	//シーン切り替え-----------------------------------------
	if (isTrigger(MOUSE_LBUTTON)) {
		State = TITLE;
	}
}
