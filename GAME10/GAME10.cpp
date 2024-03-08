#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME10.h"
namespace GAME10
{
	int GAME::create() {
		State = TITLE;
		//title・stage・resultの画像
		TitleImg = loadImage("..\\main\\assets\\game10\\title.png");
		StageImg = loadImage("..\\main\\assets\\game10\\stage.png");
		ResultImg = loadImage("..\\main\\assets\\game10\\result.png");
		//ステージで使う画像
		SCntImage = loadImage("..\\main\\assets\\game10\\scoCnt.png");
		stageSetImg = loadImage("..\\main\\assets\\game10\\stageSet.png");
		TCntImage = loadImage("..\\main\\assets\\game10\\turnCnt.png");
		//駒の画像
		Pawns.RedP = loadImage("..\\main\\assets\\game10\\red.png");
		Pawns.BlueP = loadImage("..\\main\\assets\\game10\\blue.png");
		Pawns.GreenP = loadImage("..\\main\\assets\\game10\\green.png");
		Pawns.YellowP = loadImage("..\\main\\assets\\game10\\yellow.png");
		Pawns.PinkP = loadImage("..\\main\\assets\\game10\\pink.png");
		Pawns.WhiteP = loadImage("..\\main\\assets\\game10\\white.png");
		Pawns.SpaceP = loadImage("..\\main\\assets\\game10\\space.png");
		//タイトルのbuttonの画像
		TimeButton[0] = loadImage("..\\main\\assets\\game10\\button0.png");
		TimeButton[1] = loadImage("..\\main\\assets\\game10\\button1.png");
		TimeButton[2] = loadImage("..\\main\\assets\\game10\\button2.png");
		TimeButton[3] = loadImage("..\\main\\assets\\game10\\button3.png");
		//ジャッチ用コマの画像
		JudgePawns.AnsPerfect = loadImage("..\\main\\assets\\game10\\perfectPin.png");
		JudgePawns.AnsImPerfect = loadImage("..\\main\\assets\\game10\\imPerfectPin.png");
		JudgePawns.AnsSpace = loadImage("..\\main\\assets\\game10\\JudgeSpape.png");
		//効果音
		SelectSound = loadSound("..\\main\\assets\\game10\\modeSound.wav");
		PushSound = loadSound("..\\main\\assets\\game10\\pushSound.wav");
		SetSound = loadSound("..\\main\\assets\\game10\\setSound.wav");
		JudgeSound = loadSound("..\\main\\assets\\game10\\JudgeSound.wav");
		ClearSound = loadSound("..\\main\\assets\\game10\\clearSound.wav");
		OverSound = loadSound("..\\main\\assets\\game10\\overSound.wav");
		Bgm = loadSound("..\\main\\assets\\game10\\BGM.wav");
		//駒の入れ物
		Box = new int[Row * Col];
		Click = new int[PawnsKind];
		Ans = new int[AnsCnt];
		JudgeP = new int[Row * Col];
		Colli = new COLLISION[Row * Col];
		ClickColli = new COLLISION[PawnsKind];
		Time = new TIME[TimeKind];
		BoxSize = new float[Row * Col];
		ClickSize = new float[PawnsKind];
		//Timeのみ、ここで初期化する
		for (int i = 0; i < TimeKind; i++) {
			Time[i].Tpx = Otpx + Tmx * i;
			Time[i].Tpy = Otpy;
			Time[i].DistanceX = 0;
			Time[i].DistanceY = 0;
			Time[i].Tscale = 1.0f;
			Time[i].Dist = 0;
			Time[i].TimeDecision = i;
		}
		return 0;
	}

	void GAME::destroy() {
		delete Box;
		delete Click;
		delete Ans;
		delete Colli;
		delete ClickColli;
		delete Time;
		delete BoxSize;
		delete ClickSize;
	}

	void GAME::proc() {
		if (State == TITLE) { title(); }
		else if (State == STAGE) { stage(); }
		else if (State == RESULT) { result(); }
	}

	void GAME::title() {
		clear(0);
		rectMode(CENTER);
		setTimeColli();
		image(TitleImg, width/2, Height/2);
		drawTbutton();
		//ステージへ
		if (VoiceFlag == false) {
			playSound(SelectSound);//選択してください、という音声が鳴る
			VoiceFlag = true;
		}
		if (DecisionFlag == true) {
			playSound(PushSound);
			init();
			State = STAGE;
		}
		//メニューに戻る------------------------------------------
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}

	void GAME::setTimeColli() {
		for (int i = 0; i < TimeKind; i++) {
			Time[i].DistanceX = abs(Time[i].Tpx - MouseX);
			Time[i].DistanceY = abs(Time[i].Tpy - MouseY);
			Time[i].Dist = sqrt(Time[i].DistanceX * Time[i].DistanceX + Time[i].DistanceY * Time[i].DistanceY);
			if (Time[i].Dist < Tradius / 2) {
				Time[i].Tscale = 1.5f;
			}
			else {
				Time[i].Tscale = 1.0f;
			}
			if (Time[i].Dist < Tradius / 2 && isTrigger(MOUSE_LBUTTON)) {
				SetTime = Time[i].TimeDecision;
				DecisionFlag = true;
			}
		}
	}

	void GAME::drawTbutton() {
		rectMode(CENTER);
		for (int i = 0; i < TimeKind; i++) {
			image(TimeButton[i], Time[i].Tpx, Time[i].Tpy,0,Time[i].Tscale);
		}
	}

	void GAME::init() {
		ElapsedTurns = 0;//経過ターンのリセット

		ClickBox = PawnsKind;//clickの中身初期化

		ClearFlag = false;//クリア判定の初期化

		playSound(Bgm);//音楽を鳴らす

		DecisionFlag = false;//時間決定のフラッグを折る

		VoiceFlag = false;//タイトルに戻ったら音が鳴るようにする

		NotInFlag = false;

		//設置画像サイズの初期化
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				BoxSize[Row * i + j] = DefaultSize;
			}
		}

		//選択用画像サイズの初期化
		for (int i = 0; i < PawnsKind; i++) {
			ClickSize[i] = DefaultSize;
		}

		//全部空白にする
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				Box[Row * i + j] = Space;
			}
		}

		//当たり判定の位置設定
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				Colli[Row * i + j].Cx = Px + Mx * i;
				Colli[Row * i + j].Cy = Py + My * j;
				Colli[Row * i + j].DistanceX = 0;
				Colli[Row * i + j].DistanceY = 0;
				Colli[Row * i + j].Dist = 0;
			}
		}

		//選択用駒の配置
		for (int i = 0; i < PawnsKind; i++) {
			Click[i] = i;
		}

		//選択駒の当たり判定
		for (int i = 0; i < PawnsKind; i++) {
			ClickColli[i].Cx = Kpx + Kmx * i;
			ClickColli[i].Cy = Kpy;
			ClickColli[i].DistanceX = 0;
			ClickColli[i].DistanceY = 0;
			ClickColli[i].Dist = 0;
		}

		//答えを用意
		for (int i = 0; i < AnsCnt; i++) {
			Ans[i] = random() % PawnsKind;
			for (int j = 0; j < i; j++) {//もしかぶっていた場合、もう一度入れなおす
				if (Ans[i] == Ans[j]) {
					i--;
					break;
				}
			}
		}

		//ジャッチメント用駒の初期化
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				JudgeP[Row * i + j] = AnsSpace;
			}
		}

		//時間設定
		if (SetTime != 0) {
			SumTime = DefaultTime * SetTime * Flame + Flame;//制限時間を計算
			TempTime = SumTime;
		}
	}

	void GAME::stage() {
		clear(128);
		textSize(100);
		rectMode(CENTER);
		drawDesign();
		collision();
		filldJudg();
		fill(255);
		image(TCntImage, TCx + 55, TCy - 10);//経過ターン用の画像
		text(ElapsedTurns + 1, 1680, 1000);
		print(Box[0]);
		print(Box[1]);
		print(Box[2]);
		print(Box[3]);
		print(ClickBox);
		print(PreP);
		print(ChangeFlag);
		print(NotInFlag);
		if (SetTime != 0) {
			timeLaps();//時間経過
		}
		if (isTrigger(KEY_J) && FilldFlag == true || SetTime != 0 && TempTime <= Flame) {//ターン経過
			//タイムオーバーの場合は、ターン経過のみ
			if (SetTime != 0 && TempTime <= Flame) {
				turnLapse();
			}
			else {
				judgment();
				if (ClearFlag == false) {
					playSound(JudgeSound);
					turnLapse();
				}
			}
			TempTime = SumTime;
			FilldFlag = false;
		}
		//リザルトへ(ターンがマックスターンまで経過した場合)
		if (ElapsedTurns == MaxTrun || ClearFlag == true ) {
			State = RESULT;
			if (ClearFlag == true) {
				playSound(ClearSound);
			}
			else {
				playSound(OverSound);
			}
			stopSound(Bgm);
		}
	}

	void GAME::drawDesign() {
		image(StageImg, width / 2, height / 2);
		for (int i = 0; i < 8; i++) {
			image(stageSetImg, Ipx + Imx * i, IPy);
		}
		pawnsDraw();
	}

	void GAME::timeLaps() {
		fill(255);
		image(SCntImage, SCx + 55, SCy - 70);
		if (TempTime / Flame < 10) {
			text(TempTime / Flame, SCx + Smx, SCy);
		}
		else {
			text(TempTime / Flame, SCx, SCy);
		}
		TempTime -= DeltaTime;
	}

	void GAME::pawnsDraw() {
		//駒の配置
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				switch(Box[Row*i+j]){
					case Red:
						image(Pawns.RedP, Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, 0, BoxSize[Row * i + j]);
					break;
					case Blue:
						image(Pawns.BlueP, Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, 0 ,BoxSize[Row * i + j]);
					break;
					case Green:
						image(Pawns.GreenP, Colli[Row * i + j].Cx, Colli[Row * i + j].Cy ,0, BoxSize[Row * i + j]);
					break;
					case Yellow:
						image(Pawns.YellowP, Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, 0, BoxSize[Row * i + j]);
					break;
					case Pink:
						image(Pawns.PinkP, Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, 0, BoxSize[Row * i + j]);
					break;
					case White:
						image(Pawns.WhiteP, Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, 0, BoxSize[Row * i + j]);
					break;
					case Space:
						image(Pawns.SpaceP, Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, 0, BoxSize[Row * i + j]);
					break;
				}
			}
		}

		//選択用の駒
		for (int i = 0; i < PawnsKind; i++) {
			switch (Click[i]) {
			case Red:
				image(Pawns.RedP, ClickColli[i].Cx, ClickColli[i].Cy, 0, ClickSize[i]);
				break;
			case Blue:
				image(Pawns.BlueP, ClickColli[i].Cx, ClickColli[i].Cy, 0, ClickSize[i]);
				break;
			case Green:
				image(Pawns.GreenP, ClickColli[i].Cx, ClickColli[i].Cy, 0, ClickSize[i]);
				break;
			case Yellow:
				image(Pawns.YellowP, ClickColli[i].Cx, ClickColli[i].Cy, 0, ClickSize[i]);
				break;
			case Pink:
				image(Pawns.PinkP, ClickColli[i].Cx, ClickColli[i].Cy, 0, ClickSize[i]);
				break;
			case White:
				image(Pawns.WhiteP, ClickColli[i].Cx, ClickColli[i].Cy, 0, ClickSize[i]);
				break;
			}
		}
		
		//ジャッチ用の駒表示
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				switch (JudgeP[Row * i + j]) {
				case AnsPerfect:
					image(JudgePawns.AnsPerfect, Jpx + Jmmx * ((Row * i + j) % 2) + Jbmx * i, Jpy + Jmy * (j / 2));
					break;
				case AnsImPerfect:
					image(JudgePawns.AnsImPerfect, Jpx + Jmmx * ((Row * i + j) % 2) + Jbmx * i, Jpy + Jmy * (j / 2));
					break;
				case AnsSpace:
					image(JudgePawns.AnsSpace, Jpx + Jmmx * ((Row * i + j) % 2) + Jbmx * i, Jpy + Jmy * (j / 2));
					break;
				}
			}
		}

		//ホールド中の駒
		if (ClickBox != PawnsKind) {//ホールド辞めたらここで描画が終わる
			switch (ClickBox) {
			case Red:
				image(Pawns.RedP, MouseX, MouseY, 0, BigSize);
				break;
			case Blue:
				image(Pawns.BlueP, MouseX, MouseY, 0, BigSize);
				break;
			case Green:
				image(Pawns.GreenP, MouseX, MouseY, 0, BigSize);
				break;
			case Yellow:
				image(Pawns.YellowP, MouseX, MouseY, 0, BigSize);
				break;
			case Pink:
				image(Pawns.PinkP, MouseX, MouseY, 0, BigSize);
				break;
			case White:
				image(Pawns.WhiteP, MouseX, MouseY, 0, BigSize);
				break;
			}
		}
	}

	void GAME::collision() {
		for (int i = ElapsedTurns ; i <= ElapsedTurns ; i++) {//設置する場所の判定
			fill(255, 0, 0,100);
			//現在設置する場所の表示とクリッカーとの距離の計算用の数値
			for (int j = 0; j < Row; j++) {
				if (Box[Row * i + j] == Space) {
					circle(Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, Radius-5);
				}
				Colli[Row * i + j].DistanceX = abs(Colli[Row * i + j].Cx - MouseX);
				Colli[Row * i + j].DistanceY = abs(Colli[Row * i + j].Cy - MouseY);
				Colli[Row * i + j].Dist = sqrt(Colli[Row * i + j].DistanceX * Colli[Row * i + j].DistanceX + Colli[Row * i + j].DistanceY * Colli[Row * i + j].DistanceY);

				//もし、範囲内に入った場合画像を肥大化
				if (Colli[Row * i + j].Dist < Radius / 2) {
					BoxSize[Row * i + j] = BigSize;
				}
				else {
					BoxSize[Row * i + j] = DefaultSize;
				}

				//範囲内に入ってホールドクリックをやめた場合、駒を入れ込む
				if (Colli[Row * i + j].Dist < Radius / 2 && ClickBox != PawnsKind && isRelease(MOUSE_LBUTTON) && ChangeFlag == false) {
						playSound(SetSound);
						Box[Row * i + j] = ClickBox;
						ClickBox = PawnsKind;
				}
				//設置場所でホールドした場合、持ち上げてなくす
				if (Colli[Row * i + j].Dist < Radius / 2 && isPress(MOUSE_LBUTTON) && ClickBox == PawnsKind) {
					ClickBox = Box[Row * i + j];
					PreP = Row * i + j;
					Box[Row * i + j] = Space;
					ChangeFlag = true;
				}
				//４つの当たり判定から外に出ているかを判断する
				NotInFlag = true;
				for (int x = 0; x < Row; x++) {
					if (Colli[Row * i + x].Dist > Radius / 2) {
					}
					else {
						NotInFlag = false;
						break;
					}
				}

				//設置場所から動かしたとき、入れ替える場合はこの処理
				if (isRelease(MOUSE_LBUTTON) && Colli[Row * i + j].Dist < Radius / 2 && ChangeFlag == true && NotInFlag  == false && Row * i + j != PreP) {
					playSound(SetSound);
					TempP = Box[Row * i + j];
					Box[Row * i + j] = ClickBox;
					Box[PreP] = TempP;
					ChangeFlag = false;
					TempP = false;
					PreP = false;
				}
				//設置場所とは別の場所に入れようとしたら、元の場所に戻る
				else if (isRelease(MOUSE_LBUTTON) && NotInFlag == true && ChangeFlag == true) {
					Box[PreP] = ClickBox;
					ChangeFlag = false;
				}
				//もし同じ場所に入れ込んだ場合、元の位置に戻る
				else if (isRelease(MOUSE_LBUTTON) && NotInFlag == false && Colli[Row * i + j].Dist < Radius / 2 && Row * i + j == PreP && ChangeFlag == true) {
					Box[PreP] = ClickBox;
					ChangeFlag = false;
				}

			}
		}

		//ホールドをやめたら、クリック保持を終わる
		if (isRelease(MOUSE_LBUTTON)) {
			ClickBox = PawnsKind;
		}

		for (int i = 0; i < PawnsKind; i++) {//選択する場所の判定
			ClickColli[i].DistanceX = abs(ClickColli[i].Cx - MouseX);
			ClickColli[i].DistanceY = abs(ClickColli[i].Cy - MouseY);
			ClickColli[i].Dist = sqrt(ClickColli[i].DistanceX * ClickColli[i].DistanceX + ClickColli[i].DistanceY * ClickColli[i].DistanceY);
			//範囲内に入ったら画像肥大化
			if (ClickColli[i].Dist < Radius / 2) {
				ClickSize[i] = BigSize;
			}
			else {
				ClickSize[i] = DefaultSize;
			}
			//ホールドされていて、クリックした場所が範囲内だった場合　駒のホールド開始
			if (isPress(MOUSE_LBUTTON) && ClickColli[i].Dist < Radius / 2 && ClickBox == PawnsKind) {
				ClickBox = i;
			}
		}

	}

	void GAME::turnLapse() {
			ElapsedTurns++;
	}

	void GAME::filldJudg() {//全部埋まってるかの判定 
		FilldCnt = 0;
		for (int j = 0; j < Row; j++) {
			if (Box[Row * ElapsedTurns + j] != PawnsKind) {
				FilldCnt++;
			}
		}
		if (FilldCnt == MaxFilld) {
			FilldFlag = true;
		}
	}

	void GAME::judgment(){
		//正解数・完全一致数・不完全一致数をリセット
		CorrectCnt = 0;
		PerfectCnt = 0;
		ImPerfectCnt = 0;
		SameKindCnt = 0;
		//正解数をカウント
			for (int i = 0; i < Row; i++) {
				if (Ans[i] == Box[Row * ElapsedTurns + i]) {
					CorrectCnt++;
				}
			}
			//全部あっていた場合
			if (CorrectCnt == AnsCnt) {
				ClearFlag = true;
			}
			//一部正解だった場合
			else {
				for (int i = 0; i < Row; i++) {//完全一致をカウント
					if (Ans[i] == Box[Row * ElapsedTurns + i]) {
						PerfectCnt++;
					}
				}

				for (int i = 0; i < Row - 1; i++) {//回答にかぶりが何個あるかを数える
						for (int j = i; j < Row; j++) {
							if (Box[Row * ElapsedTurns + i] == Box[Row * ElapsedTurns + j] && i != j) {//解答用の場所に同じ色があった場合
								for (int k = 0; k < Row; k++) {
									if (Box[Row * ElapsedTurns + i] == Ans[k]) {//答えと回答に同じ色があった場合
										SameKindCnt++;
										break;
									}
								}
								break;
							}
						}
					}
				for (int i = 0; i < Row; i++) {//不完全一致をカウント
					for (int j = 0; j < Row; j++) {
						if (Ans[i] == Box[Row * ElapsedTurns + j] && i != j) {
							ImPerfectCnt++;
						}
					}
				}
				if (ImPerfectCnt >= SameKindCnt) {
					ImPerfectCnt = ImPerfectCnt - SameKindCnt;//不完全一致とかぶりの数の差を出す。
				}
				for (int i = 0; i < Row; i++) {
					if (PerfectCnt > 0) {//完全一致がゼロより多い場合はヒットのピンを入れる
						JudgeP[Row * ElapsedTurns + i] = AnsPerfect;
						PerfectCnt--;
					}
					else if (ImPerfectCnt > 0) {//不完全一致だった場合、ブローのピンを入れる
						JudgeP[Row * ElapsedTurns + i] = AnsImPerfect;
						ImPerfectCnt--;
					}
					else {//両方とも０だった場合空白にする
						JudgeP[Row * ElapsedTurns + i] = AnsSpace;
					}
				}
			}
		//サイズをすべてデフォルトに戻す
			for (int i = ElapsedTurns; i <= ElapsedTurns; i++) {
				for (int j = 0; j < Row; j++) {
					BoxSize[Row * i + j] = DefaultSize;
				}
			}
	}

	void GAME::result() {
		clear(128,128,128);
		drawDesign();
		image(ResultImg, width / 2, Height / 2);
		fill(255);
		textSize(125);
		rectMode(CENTER);
		if (ElapsedTurns == MaxTrun) {
			text("もう一度挑戦しよう!", width/2 - 630, 200);
			text("スペースキーでタイトルに戻る", 100, 900);
		}
		else {
			text("congratulation!!", width / 2 - 500, 200);
			textSize(70);
			text(ElapsedTurns + 1, 660, 300);
			text("あなたは　ターンでクリアしました！", 350, 300);
			textSize(125);
			text("スペースキーでタイトルに戻る", 100 , 900);
		}
		//タイトルへ
		if (isTrigger(KEY_SPACE)) {
			State = TITLE;
		}
	}

/*
	int GAME::create()
	{
		//ここでは主に画像と音データを読み込む

		//初期値設定はInit()関数などを作ってそこで行ったほうが良い。
		//シンプルなゲームなら次のように、ここで行ってもよい。
		Px = width / 2;
		Py = height / 2;
		Radius = 200;

		return 0;
	}

	void GAME::destroy()
	{
		//create()でnewした場合はここでdeleteすること
	}

	void GAME::proc()
	{
		//ここはメインループから呼び出されている!!!!!

		//描画--------------------------------------------------
		clear(255, 255, 255);
		//円
		strokeWeight(50);
		stroke(0);
		fill(255, 0, 0);
		circle(Px, Py, Radius * 2);
		//テキスト情報
		fill(0);
		textSize(100);
		print(Mx);
		text("Enterでメニューに戻る", 0, height);
		print(10);
		//反射と反復の切り替え
		if (isTrigger(MOUSE_LBUTTON)) {
			changeFlag = false;
			Px = Width / 2;
			Py = height / 2;
			if (Mx <= 0) {//もし、Xがマイナス側に動く場合は　プラスに戻す
				Mx *= -1;
			}
		}
		if (isTrigger(MOUSE_RBUTTON)) {
			changeFlag = true;
			Px = Width / 2;
			Py = height / 2;
		}

		if (changeFlag == false) {//反復
			Px += Mx;
			if (Px >= width + Radius + 50) {
				Px = 0 - Radius - 50;
			}
		}

		if (changeFlag == true) {//反射
			Px += Mx;
			Py += My;
			if (Px + Radius>= width || Px - Radius<= 0) {
				Mx *= -1;
			}
			if (Py + Radius>= height || Py - Radius<= 0) {
				My *= -1;
			}
		}
		//メニューに戻る------------------------------------------
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
	*/
}