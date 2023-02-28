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
	Rows = 2;//行
	Cols = 3;//列
	TileW = 160 * 3;
	TileH = 90 * 3;
	OfstX = (width - TileW * Cols) / 2;
	OfstY = (height - TileH * Rows) / 2;
	DivHue = 360.0f / (Cols * Rows);
	SizeText = 40;
	IndexMouseHolding = -1;

	LoadIndices();
	LoadTitleNames();

	return 0;
}

void MENU::LoadIndices()
{
	//メニューに並べるレベルのインデックス番号の配列確保
	NumIndices = Rows * Cols;
	Indices = new char[NumIndices] {};
	//メニューに並べるレベルのインデックス番号ファイルをIndices配列に読み込む
	const char* fileName = "../MAIN/assets/menu/indices.bin";
	std::ifstream ifs(fileName, std::ios::binary);
	if (ifs) {
		//一気に読み込む。もろもろのエラー処理はしていない。
		ifs.read(Indices, NumIndices);
		ifs.close();
	}
	else {
		//ファイルが無ければ連番を設定
		for (int i = 0; i < NumIndices; i++) {
			Indices[i] = i;
		}
	}
}

void MENU::LoadTitleNames()
{
	//タイルに表示するレベルタイトルのテキストを読み込む配列確保
	Titles = new std::string[NumIndices];
	//タイルに表示するレベルタイトルのテキストをファイルから読み込む
	std::ifstream ifs;
	char buf[128];
	for (int i = 0; i < NumIndices; i++) {
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
	ofs.write(Indices, NumIndices);

	delete[] Titles;
	delete[] Indices;
}


void MENU::proc()
{
	//更新--------------------------------------------------
	ChangePosition();
	//描画--------------------------------------------------
	Draw();
	//右クリックで選択したレベルに切り替え-----------------------
	if (isTrigger(MOUSE_LBUTTON)) {
		if (IndexMouseOver >= 0) {
			int index = Indices[IndexMouseOver];
			main()->setNextLevelId((LEVEL_FACTORY::LEVEL_ID)index);
		}
	}
}

void MENU::ChangePosition()
{
	//左クリックによるドラッグアンドドロップでレベルの順序を並び変える

	//マウスが乗っているタイルのインデックス。とりあえず無効(-1)
	IndexMouseOver = -1;
	//マウスがメニュー（全タイル）の範囲にあるなら
	if (mouseX > OfstX && mouseX < OfstX + TileW * Cols &&
		mouseY > OfstY && mouseY < OfstY + TileH * Rows)
	{
		//マウスの位置から列番号と行番号に変換
		int mouseCol = int((mouseX - OfstX) / TileW);
		int mouseRow = int((mouseY - OfstY) / TileH);
		//１次元配列Indices[]のインデックスに変換
		IndexMouseOver = Cols * mouseRow + mouseCol;
		//「掴む！」クリックされた時のインデックスを取っておく
		if (isTrigger(MOUSE_RBUTTON))
		{
			IndexMouseHolding = IndexMouseOver;
		}
		//「離す！」マウスボタンを離した位置にとっておいたインデックスを挿入
		if (IndexMouseHolding != -1 &&
			isRelease(MOUSE_RBUTTON))
		{
			//クリックされたタイルのインデックスを取っておく
			int workIndex = Indices[IndexMouseHolding];
			//後ろのインデックスを前に持っていった時、後ろにずらす
			if (IndexMouseOver < IndexMouseHolding)
			{
				for (int i = IndexMouseHolding; i > IndexMouseOver; i--)
				{
					Indices[i] = Indices[i - 1];
				}
			}
			//前のインデックスを後ろに持っていった時、前にずらす
			else if (IndexMouseOver > IndexMouseHolding)
			{
				for (int i = IndexMouseHolding; i < IndexMouseOver; i++)
				{
					Indices[i] = Indices[i + 1];
				}
			}
			//上でずらすことにより挿入場所ができたので入れる
			Indices[IndexMouseOver] = workIndex;
			//無効にする
			IndexMouseHolding = -1;
		}
	}
	else {
		//全タイルの外に出たので、掴んでいるインデックスを無効にする
		IndexMouseHolding = -1;
	}
}

void MENU::Draw()
{
	//カラーモード、枠の色、枠の幅
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
			if (index == IndexMouseOver) {
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
			text(Titles[Indices[index]].c_str(), px + 10, py + 10 + SizeText);
		}
	}
	//移動中のタイトル文字を描画
	if (IndexMouseHolding >= 0) {
		fill(128);
		textMode(BCENTER);
		text(Titles[Indices[IndexMouseHolding]].c_str(), mouseX, mouseY);
	}
}