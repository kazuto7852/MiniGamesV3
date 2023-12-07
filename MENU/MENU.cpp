#include <fstream>
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/mathUtil.h"
#include "../MAIN/GAME_FACTORY.h"
#include "../MAIN/MAIN.h"
#include "MENU.h"

int MENU::create()
{
	//各変数初期化
	//タイルの数
	Rows = 4;//行
	Cols = 4;//列
	//タイルの大きさ
	TileW = 160*2;
	TileH = 90*2;
	//左上の原点をずらす値
	OfstX = (width - TileW * Cols) / 2;
	OfstY = (height - TileH * Rows) / 2;
	//タイルの色を決定するための分割された角度Hue
	DivHue = 360.0f / (Cols * Rows);
	//タイルの上に表示する各ゲームのタイトルの大きさ
	SizeText = 40;
	//マウスで右クリックされたタイルのインデックス。とりあえず-1で無効にしておく。
	TileIndexMouseHolding = -1;

	LoadGameIndices();
	LoadTitleNames();

	return 0;
}

void MENU::LoadGameIndices()
{
	//メニューに並べるゲームのインデックス番号の配列確保
	NumGameIndices = Rows * Cols;
	GameIndices = new char[NumGameIndices] {};
	//メニューに並べるゲームのインデックス番号ファイルをGameIndices配列に読み込む
	const char* fileName = "../MAIN/assets/menu/indices.bin";
	std::ifstream ifs(fileName, std::ios::binary);
	if (ifs) {
		//一気に読み込む。
		ifs.read(GameIndices, NumGameIndices);
		ifs.close();
	}
	else {
		//ファイルが無ければ連番を設定
		for (int i = 0; i < NumGameIndices; i++) {
			GameIndices[i] = i;
		}
	}
}

void MENU::LoadTitleNames()
{
	//タイルに表示するゲームタイトルのテキストを読み込む配列確保
	Titles = new std::string[NumGameIndices];
	//タイルに表示するゲームタイトルのテキストをファイルから読み込む
	std::ifstream ifs;
	char buf[128];
	for (int i = 0; i < NumGameIndices; i++) {
		sprintf_s(buf, "../MAIN/assets/game%02d/title.txt", i);
		ifs.open(buf);
		std::getline(ifs, Titles[i]);
		ifs.close();
	}
}

void MENU::destroy()
{
	//現在のインデックスの並びをファイルに書き込み
	const char* fileName = "../MAIN/assets/menu/indices.bin";
	std::ofstream ofs(fileName, std::ios::binary);
	ofs.write(GameIndices, NumGameIndices);

	delete[] Titles;
	delete[] GameIndices;
}

void MENU::proc()
{
	//更新--------------------------------------------------
	ChangeGameIndices();
	//描画--------------------------------------------------
	Draw();
	//左クリックで選択したゲームに切り替え-----------------------
	if (isTrigger(MOUSE_LBUTTON)) {
		if (TileIndexMouseOver >= 0) {
			int index = GameIndices[TileIndexMouseOver];
			main()->setNextGameId((GAME_FACTORY::GAME_ID)index);
		}
	}
}

//マウス右ボタンによるドラッグアンドドロップでゲームの順序を並び変える
void MENU::ChangeGameIndices()
{
	//マウスが乗っているタイルのインデックス。
	//ループごとに調べるため無効(-1)にしておく
	TileIndexMouseOver = -1;

	//マウスが全タイルの外にある時はこの関数を抜ける
	if (mouseX<OfstX || mouseX > OfstX + TileW * Cols ||
		mouseY<OfstY || mouseY > OfstY + TileH * Rows) {
		//掴んでいるインデックスを無効にする
		TileIndexMouseHolding = -1;
		return;
	}

	//ここから下はタイル上にマウスがある-------------------------
	
	//マウスの位置から列番号と行番号に変換
	int mouseCol = int((mouseX - OfstX) / TileW);
	int mouseRow = int((mouseY - OfstY) / TileH);
	//１次元配列GameIndices[]のインデックスに変換
	TileIndexMouseOver = Cols * mouseRow + mouseCol;

	//「掴む！」右クリックされたタイルのインデックスを取っておく
	if (isTrigger(MOUSE_RBUTTON)) {
		TileIndexMouseHolding = TileIndexMouseOver;
	}

	//「離す！」右ボタンを離した位置に、とっておいたインデックスを挿入
	if (isRelease(MOUSE_RBUTTON) &&
		TileIndexMouseHolding != -1) {
		//掴んでいる「ゲームのインデックス」を取っておく
		int workIndex = GameIndices[TileIndexMouseHolding];
		//後方のインデックスを前方にドラッグアンドドロップした時、後ろにずらすして挿入位置を空ける
		if (TileIndexMouseOver < TileIndexMouseHolding)	{
			for (int i = TileIndexMouseHolding; i > TileIndexMouseOver; i--) {
				GameIndices[i] = GameIndices[i - 1];
			}
		}
		//前方のインデックスを後方にドラッグアンドドロップした時、前にずらすして挿入位置を空ける
		else if (TileIndexMouseOver > TileIndexMouseHolding) {
			for (int i = TileIndexMouseHolding; i < TileIndexMouseOver; i++) {
				GameIndices[i] = GameIndices[i + 1];
			}
		}
		//ずらすことにより挿入場所ができたので入れる
		GameIndices[TileIndexMouseOver] = workIndex;
		//無効にする
		TileIndexMouseHolding = -1;
	}
}

void MENU::Draw()
{
	//カラーモード、枠の色、枠の幅、画面クリア
	colorMode(HSV);
	angleMode(DEGREES);
	stroke(0, 0, 0);
	strokeWeight(5);
	clear(0, 0, 0);
	//Menu文字描画
	textMode(BOTTOM);
	textSize(SizeText);
	fill(0, 0, 255);
	text("Menu", OfstX, OfstY);
	//タイル描画
	for (int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Cols; c++)
		{
			//タイルの色を決定
			int index = Cols * r + c;
			float hue = DivHue * index;
			float saturation = 255;
			float value = 160;
			//マウスが上にあるタイルは明るく
			if (index == TileIndexMouseOver) {
				saturation = 128;
				value = 255;
			}
			fill(hue, saturation, value);
			//タイルの位置
			float px = TileW * c + OfstX;
			float py = TileH * r + OfstY;
			rect(px, py, TileW, TileH);
			//タイトル文字
			textSize(SizeText);
			fill(0);
			textMode(BOTTOM);
			text(Titles[GameIndices[index]].c_str(), px + 10, py + 10 + SizeText);
		}
	}
	//移動中のタイトル文字を描画
	if (TileIndexMouseHolding >= 0) {
		fill(128);
		textMode(BCENTER);
		text(Titles[GameIndices[TileIndexMouseHolding]].c_str(), mouseX, mouseY);
	}
}