#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/mathUtil.h"
#include "../MAIN/LEVEL_FACTORY.h"
#include "../MAIN/MAIN.h"
#include "MENU.h"

void MENU::create()
{
	Rows = 2;//行
	Cols = 2;//列
	TileW = 160*4;
	TileH = 90*4;
	OfstX = (width - TileW * Cols) / 2;
	OfstY = (height - TileH * Rows) / 2;
	DivHue = 360.0f / (Cols * Rows);
}

void MENU::destroy()
{
}

void MENU::proc()
{
	//更新--------------------------------------------------
	//マウスが乗っているタイルのselectIndexを決定
	int selectIndex = -1;//全てのタイルの外側にいるときはー１
	if (mouseX > OfstX && mouseX<OfstX+TileW * Cols &&
		mouseY>OfstY && mouseY < OfstY+TileH * Rows) {
		int mouseCol = int((mouseX - OfstX) / TileW);
		int mouseRow = int((mouseY - OfstY) / TileH);
		selectIndex = Cols * mouseRow + mouseCol;
	}
	//描画--------------------------------------------------
	//カラーモード、枠の色、枠の幅
	colorMode(HSV);
	angleMode(DEGREES);
	stroke(0, 0, 0);
	strokeWeight(5);
	clear(0,0,0);
	//Menu文字
	float size = 40;
	textSize(size);
	fill(0, 0, 255);
	text("Menu", OfstX, OfstY);
	//タイル
	for (int r = 0; r < Rows; r++) {
		for (int c = 0; c < Cols; c++) {
			//タイルの色を決定
			int index = Cols * r + c;
			float hue = DivHue * index;
			float saturation = 200;
			//マウスが上にあるタイルは明るく
			if (index == selectIndex) {
				saturation = 0;
			}
			fill(hue, saturation, 200);
			//タイルの表示位置を決めて描画
			float px = TileW * c + OfstX;
			float py = TileH * r + OfstY;
			rect(px, py, TileW, TileH);
			//インデックス表示
			fill(0);
			text(index, px + 10, py + size + 10);
		}
	}

	if (selectIndex >= 0 &&
		isTrigger(MOUSE_LBUTTON)) {
		main()->setNextLevelId((LEVEL_FACTORY::LEVEL_ID)selectIndex);
	}
}


