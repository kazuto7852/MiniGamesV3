#include <fstream>
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/mathUtil.h"
#include "../MAIN/LEVEL_FACTORY.h"
#include "../MAIN/MAIN.h"
#include "MENU.h"

int MENU::create()
{
	//各変数初期化
	//タイルの数
	Rows = 2;//行
	Cols = 3;//列
	//タイルの大きさ
	TileW = 160 * 3;
	TileH = 90 * 3;
	//左上の原点をずらす値
	OfstX = (width - TileW * Cols) / 2;
	OfstY = (height - TileH * Rows) / 2;
	//タイルの色を決定するための分割された角度Hue
	DivHue = 360.0f / (Cols * Rows);
	//タイルの上に表示する各レベルのタイトルの大きさ
	SizeText = 40;
	//マウスで右クリックされたタイルのインデックス。とりあえず-1で無効にしておく。
	TileIndexMouseHolding = -1;

	LoadIndices();
	LoadTitleNames();

	return 0;
}

void MENU::LoadIndices()
{
	//メニューに並べるレベルのインデックス番号の配列確保
	NumLevelIndices = Rows * Cols;
	LevelIndices = new char[NumLevelIndices] {};
	//メニューに並べるレベルのインデックス番号ファイルをLevelIndices配列に読み込む
	const char* fileName = "../MAIN/assets/menu/indices.bin";
	std::ifstream ifs(fileName, std::ios::binary);
	if (ifs) {
		//一気に読み込む。
		ifs.read(LevelIndices, NumLevelIndices);
		ifs.close();
	}
	else {
		//ファイルが無ければ連番を設定
		for (int i = 0; i < NumLevelIndices; i++) {
			LevelIndices[i] = i;
		}
	}
}

void MENU::LoadTitleNames()
{
	//タイルに表示するレベルタイトルのテキストを読み込む配列確保
	Titles = new std::string[NumLevelIndices];
	//タイルに表示するレベルタイトルのテキストをファイルから読み込む
	std::ifstream ifs;
	char buf[128];
	for (int i = 0; i < NumLevelIndices; i++) {
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
	ofs.write(LevelIndices, NumLevelIndices);

	delete[] Titles;
	delete[] LevelIndices;
}


void MENU::proc()
{
	//更新--------------------------------------------------
	ChangeLevelIndices();
	//描画--------------------------------------------------
	Draw();
	//左クリックで選択したレベルに切り替え-----------------------
	if (isTrigger(MOUSE_LBUTTON)) {
		if (TileIndexMouseOver >= 0) {
			int index = LevelIndices[TileIndexMouseOver];
			main()->setNextLevelId((LEVEL_FACTORY::LEVEL_ID)index);
		}
	}
}

//マウス右ボタンによるドラッグアンドドロップでレベルの順序を並び変える
void MENU::ChangeLevelIndices()
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
	//１次元配列LevelIndices[]のインデックスに変換
	TileIndexMouseOver = Cols * mouseRow + mouseCol;

	//「掴む！」右クリックされたタイルのインデックスを取っておく
	if (isTrigger(MOUSE_RBUTTON)) {
		TileIndexMouseHolding = TileIndexMouseOver;
	}

	//「離す！」右ボタンを離した位置に、とっておいたインデックスを挿入
	if (isRelease(MOUSE_RBUTTON) &&
		TileIndexMouseHolding != -1) {
		//掴んでいる「レベルのインデックス」を取っておく
		int workIndex = LevelIndices[TileIndexMouseHolding];
		//後方のインデックスを前方にドラッグアンドドロップした時、後ろにずらすして挿入位置を空ける
		if (TileIndexMouseOver < TileIndexMouseHolding)	{
			for (int i = TileIndexMouseHolding; i > TileIndexMouseOver; i--) {
				LevelIndices[i] = LevelIndices[i - 1];
			}
		}
		//前方のインデックスを後方にドラッグアンドドロップした時、前にずらすして挿入位置を空ける
		else if (TileIndexMouseOver > TileIndexMouseHolding) {
			for (int i = TileIndexMouseHolding; i < TileIndexMouseOver; i++) {
				LevelIndices[i] = LevelIndices[i + 1];
			}
		}
		//ずらすことにより挿入場所ができたので入れる
		LevelIndices[TileIndexMouseOver] = workIndex;
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
			text(Titles[LevelIndices[index]].c_str(), px + 10, py + 10 + SizeText);
		}
	}
	//移動中のタイトル文字を描画
	if (TileIndexMouseHolding >= 0) {
		fill(128);
		textMode(BCENTER);
		text(Titles[LevelIndices[TileIndexMouseHolding]].c_str(), mouseX, mouseY);
	}
}