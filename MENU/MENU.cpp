#include <fstream>
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/mathUtil.h"
#include "../MAIN/LEVEL_FACTORY.h"
#include "../MAIN/MAIN.h"
#include "MENU.h"

void MENU::create()
{
	Rows = 2;//行
	Cols = 3;//列
	TileW = 160*3;
	TileH = 90*3;
	OfstX = (width - TileW * Cols) / 2;
	OfstY = (height - TileH * Rows) / 2;
	DivHue = 360.0f / (Cols * Rows);
	SizeText = 40;

	//
	NumIndices = Rows * Cols;
	Indices = new char[NumIndices];
	const char* fileName = "../MAIN/assets/menu/indices.bin";
	std::ifstream ifs(fileName, std::ios::binary);
	if (ifs) {
		ifs.read(Indices, NumIndices);
		for (int i = 0; i < NumIndices; i++) {
			if (Indices[i] == -51) {
				Indices[i] = i;
			}
		}
	}
	else {
		for (int i = 0; i < NumIndices; i++) {
			Indices[i] = i;
		}
	}
	ifs.close();

	//タイルに表示するタイトルテキスト
	Titles = new std::string[NumIndices];
	char buf[128];
	for (int i = 0; i < NumIndices; i++) {
		sprintf_s(buf,"../MAIN/assets/game%02d/title.txt",i);
		ifs.open(buf);
		std::getline(ifs,Titles[i]);
		ifs.close();
	}

	IndexMouseHolding = -1;
}

void MENU::destroy()
{
	const char* fileName = "../MAIN/assets/menu/indices.bin";
	std::ofstream ofs(fileName, std::ios::binary);
	ofs.write(Indices, NumIndices);
	
	delete[] Titles;
	delete[] Indices;
}

void MENU::proc()
{
	//更新--------------------------------------------------
	//マウスが乗っているタイルのselectIndexを決定
		//マウスがあるタイルのインデックス
	int indexMouseOver = -1;
	//マウスがメニュー（全タイル）の範囲にある
	if (mouseX > OfstX && mouseX < OfstX + TileW * Cols &&
		mouseY > OfstY && mouseY < OfstY + TileH * Rows)
	{
		//マウスの位置から列番号と行番号に変換
		int mouseCol = int((mouseX - OfstX) / TileW);
		int mouseRow = int((mouseY - OfstY) / TileH);
		//１次元配列Indices[]のインデックスに変換
		indexMouseOver = Cols * mouseRow + mouseCol;
		//クリックされた時のインデックスを取っておく
		if (isTrigger(MOUSE_RBUTTON))
		{
			IndexMouseHolding = indexMouseOver;
		}
		//マウスボタンを離した位置にとっておいたインデックスを挿入
		if (IndexMouseHolding != -1 &&
			isRelease(MOUSE_RBUTTON))
		{
			//クリックされたタイルのインデックスを取っておく
			int workIndex = Indices[IndexMouseHolding];
			//後ろのインデックスを前に持っていった時、後ろにずらす
			if (indexMouseOver < IndexMouseHolding)
			{
				for (int i = IndexMouseHolding; i > indexMouseOver; i--)
				{
					Indices[i] = Indices[i - 1];
				}
			}
			//前のインデックスを後ろに持っていった時、前にずらす
			else if (indexMouseOver > IndexMouseHolding)
			{
				for (int i = IndexMouseHolding; i < indexMouseOver; i++)
				{
					Indices[i] = Indices[i + 1];
				}
			}
			//上でずらすことにより挿入場所ができたので入れる
			Indices[indexMouseOver] = workIndex;
			//無効にする
			IndexMouseHolding = -1;
		}
	}
	else {
		//無効にする
		IndexMouseHolding = -1;
	}
	//描画--------------------------------------------------
	//カラーモード、枠の色、枠の幅
	colorMode(HSV);
	angleMode(DEGREES);
	stroke(0, 0, 0);
	strokeWeight(5);
	clear(0,0,0);
	//Menu文字
	textMode(BOTTOM);
	textSize(SizeText);
	fill(0, 0, 255);
	text("Menu", OfstX, OfstY);
	//タイル
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
			if (index == indexMouseOver) {
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
			text(Titles[Indices[index]].c_str(), px+10, py +10+ SizeText);
		}
	}
	if (IndexMouseHolding >= 0) {
		fill(128);
		textMode(BCENTER);
		text(Titles[Indices[IndexMouseHolding]].c_str(), mouseX, mouseY);
	}
	//for (int r = 0; r < Rows; r++) {
	//	for (int c = 0; c < Cols; c++) {
	//		//タイルの色を決定
	//		int index = Cols * r + c;
	//		float hue = DivHue * index;
	//		float saturation = 200;
	//		//マウスが上にあるタイルは明るく
	//		if (index == selectIndex) {
	//			saturation = 0;
	//		}
	//		fill(hue, saturation, 200);
	//		//タイルの表示位置を決めて描画
	//		float px = TileW * c + OfstX;
	//		float py = TileH * r + OfstY;
	//		rect(px, py, TileW, TileH);
	//		//インデックス表示
	//		fill(0);
	//		text(index, px + 10, py + size + 10);
	//	}
	//}

	if (Indices[indexMouseOver] >= 0 &&
		isTrigger(MOUSE_LBUTTON)) {
		main()->setNextLevelId(
			(LEVEL_FACTORY::LEVEL_ID)Indices[indexMouseOver]);
	}
}


