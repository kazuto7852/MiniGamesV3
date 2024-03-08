#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME10.h"
namespace GAME10
{
	int GAME::create() {
		State = TITLE;
		//title�Estage�Eresult�̉摜
		TitleImg = loadImage("..\\main\\assets\\game10\\title.png");
		StageImg = loadImage("..\\main\\assets\\game10\\stage.png");
		ResultImg = loadImage("..\\main\\assets\\game10\\result.png");
		//�X�e�[�W�Ŏg���摜
		SCntImage = loadImage("..\\main\\assets\\game10\\scoCnt.png");
		stageSetImg = loadImage("..\\main\\assets\\game10\\stageSet.png");
		TCntImage = loadImage("..\\main\\assets\\game10\\turnCnt.png");
		//��̉摜
		Pawns.RedP = loadImage("..\\main\\assets\\game10\\red.png");
		Pawns.BlueP = loadImage("..\\main\\assets\\game10\\blue.png");
		Pawns.GreenP = loadImage("..\\main\\assets\\game10\\green.png");
		Pawns.YellowP = loadImage("..\\main\\assets\\game10\\yellow.png");
		Pawns.PinkP = loadImage("..\\main\\assets\\game10\\pink.png");
		Pawns.WhiteP = loadImage("..\\main\\assets\\game10\\white.png");
		Pawns.SpaceP = loadImage("..\\main\\assets\\game10\\space.png");
		//�^�C�g����button�̉摜
		TimeButton[0] = loadImage("..\\main\\assets\\game10\\button0.png");
		TimeButton[1] = loadImage("..\\main\\assets\\game10\\button1.png");
		TimeButton[2] = loadImage("..\\main\\assets\\game10\\button2.png");
		TimeButton[3] = loadImage("..\\main\\assets\\game10\\button3.png");
		//�W���b�`�p�R�}�̉摜
		JudgePawns.AnsPerfect = loadImage("..\\main\\assets\\game10\\perfectPin.png");
		JudgePawns.AnsImPerfect = loadImage("..\\main\\assets\\game10\\imPerfectPin.png");
		JudgePawns.AnsSpace = loadImage("..\\main\\assets\\game10\\JudgeSpape.png");
		//���ʉ�
		SelectSound = loadSound("..\\main\\assets\\game10\\modeSound.wav");
		PushSound = loadSound("..\\main\\assets\\game10\\pushSound.wav");
		SetSound = loadSound("..\\main\\assets\\game10\\setSound.wav");
		JudgeSound = loadSound("..\\main\\assets\\game10\\JudgeSound.wav");
		ClearSound = loadSound("..\\main\\assets\\game10\\clearSound.wav");
		OverSound = loadSound("..\\main\\assets\\game10\\overSound.wav");
		Bgm = loadSound("..\\main\\assets\\game10\\BGM.wav");
		//��̓��ꕨ
		Box = new int[Row * Col];
		Click = new int[PawnsKind];
		Ans = new int[AnsCnt];
		JudgeP = new int[Row * Col];
		Colli = new COLLISION[Row * Col];
		ClickColli = new COLLISION[PawnsKind];
		Time = new TIME[TimeKind];
		BoxSize = new float[Row * Col];
		ClickSize = new float[PawnsKind];
		//Time�̂݁A�����ŏ���������
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
		//�X�e�[�W��
		if (VoiceFlag == false) {
			playSound(SelectSound);//�I�����Ă��������A�Ƃ�����������
			VoiceFlag = true;
		}
		if (DecisionFlag == true) {
			playSound(PushSound);
			init();
			State = STAGE;
		}
		//���j���[�ɖ߂�------------------------------------------
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
		ElapsedTurns = 0;//�o�߃^�[���̃��Z�b�g

		ClickBox = PawnsKind;//click�̒��g������

		ClearFlag = false;//�N���A����̏�����

		playSound(Bgm);//���y��炷

		DecisionFlag = false;//���Ԍ���̃t���b�O��܂�

		VoiceFlag = false;//�^�C�g���ɖ߂����特����悤�ɂ���

		NotInFlag = false;

		//�ݒu�摜�T�C�Y�̏�����
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				BoxSize[Row * i + j] = DefaultSize;
			}
		}

		//�I��p�摜�T�C�Y�̏�����
		for (int i = 0; i < PawnsKind; i++) {
			ClickSize[i] = DefaultSize;
		}

		//�S���󔒂ɂ���
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				Box[Row * i + j] = Space;
			}
		}

		//�����蔻��̈ʒu�ݒ�
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				Colli[Row * i + j].Cx = Px + Mx * i;
				Colli[Row * i + j].Cy = Py + My * j;
				Colli[Row * i + j].DistanceX = 0;
				Colli[Row * i + j].DistanceY = 0;
				Colli[Row * i + j].Dist = 0;
			}
		}

		//�I��p��̔z�u
		for (int i = 0; i < PawnsKind; i++) {
			Click[i] = i;
		}

		//�I����̓����蔻��
		for (int i = 0; i < PawnsKind; i++) {
			ClickColli[i].Cx = Kpx + Kmx * i;
			ClickColli[i].Cy = Kpy;
			ClickColli[i].DistanceX = 0;
			ClickColli[i].DistanceY = 0;
			ClickColli[i].Dist = 0;
		}

		//������p��
		for (int i = 0; i < AnsCnt; i++) {
			Ans[i] = random() % PawnsKind;
			for (int j = 0; j < i; j++) {//�������Ԃ��Ă����ꍇ�A������x����Ȃ���
				if (Ans[i] == Ans[j]) {
					i--;
					break;
				}
			}
		}

		//�W���b�`�����g�p��̏�����
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				JudgeP[Row * i + j] = AnsSpace;
			}
		}

		//���Ԑݒ�
		if (SetTime != 0) {
			SumTime = DefaultTime * SetTime * Flame + Flame;//�������Ԃ��v�Z
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
		image(TCntImage, TCx + 55, TCy - 10);//�o�߃^�[���p�̉摜
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
			timeLaps();//���Ԍo��
		}
		if (isTrigger(KEY_J) && FilldFlag == true || SetTime != 0 && TempTime <= Flame) {//�^�[���o��
			//�^�C���I�[�o�[�̏ꍇ�́A�^�[���o�߂̂�
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
		//���U���g��(�^�[�����}�b�N�X�^�[���܂Ōo�߂����ꍇ)
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
		//��̔z�u
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

		//�I��p�̋�
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
		
		//�W���b�`�p�̋�\��
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

		//�z�[���h���̋�
		if (ClickBox != PawnsKind) {//�z�[���h���߂��炱���ŕ`�悪�I���
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
		for (int i = ElapsedTurns ; i <= ElapsedTurns ; i++) {//�ݒu����ꏊ�̔���
			fill(255, 0, 0,100);
			//���ݐݒu����ꏊ�̕\���ƃN���b�J�[�Ƃ̋����̌v�Z�p�̐��l
			for (int j = 0; j < Row; j++) {
				if (Box[Row * i + j] == Space) {
					circle(Colli[Row * i + j].Cx, Colli[Row * i + j].Cy, Radius-5);
				}
				Colli[Row * i + j].DistanceX = abs(Colli[Row * i + j].Cx - MouseX);
				Colli[Row * i + j].DistanceY = abs(Colli[Row * i + j].Cy - MouseY);
				Colli[Row * i + j].Dist = sqrt(Colli[Row * i + j].DistanceX * Colli[Row * i + j].DistanceX + Colli[Row * i + j].DistanceY * Colli[Row * i + j].DistanceY);

				//�����A�͈͓��ɓ������ꍇ�摜���剻
				if (Colli[Row * i + j].Dist < Radius / 2) {
					BoxSize[Row * i + j] = BigSize;
				}
				else {
					BoxSize[Row * i + j] = DefaultSize;
				}

				//�͈͓��ɓ����ăz�[���h�N���b�N����߂��ꍇ�A�����ꍞ��
				if (Colli[Row * i + j].Dist < Radius / 2 && ClickBox != PawnsKind && isRelease(MOUSE_LBUTTON) && ChangeFlag == false) {
						playSound(SetSound);
						Box[Row * i + j] = ClickBox;
						ClickBox = PawnsKind;
				}
				//�ݒu�ꏊ�Ńz�[���h�����ꍇ�A�����グ�ĂȂ���
				if (Colli[Row * i + j].Dist < Radius / 2 && isPress(MOUSE_LBUTTON) && ClickBox == PawnsKind) {
					ClickBox = Box[Row * i + j];
					PreP = Row * i + j;
					Box[Row * i + j] = Space;
					ChangeFlag = true;
				}
				//�S�̓����蔻�肩��O�ɏo�Ă��邩�𔻒f����
				NotInFlag = true;
				for (int x = 0; x < Row; x++) {
					if (Colli[Row * i + x].Dist > Radius / 2) {
					}
					else {
						NotInFlag = false;
						break;
					}
				}

				//�ݒu�ꏊ���瓮�������Ƃ��A����ւ���ꍇ�͂��̏���
				if (isRelease(MOUSE_LBUTTON) && Colli[Row * i + j].Dist < Radius / 2 && ChangeFlag == true && NotInFlag  == false && Row * i + j != PreP) {
					playSound(SetSound);
					TempP = Box[Row * i + j];
					Box[Row * i + j] = ClickBox;
					Box[PreP] = TempP;
					ChangeFlag = false;
					TempP = false;
					PreP = false;
				}
				//�ݒu�ꏊ�Ƃ͕ʂ̏ꏊ�ɓ���悤�Ƃ�����A���̏ꏊ�ɖ߂�
				else if (isRelease(MOUSE_LBUTTON) && NotInFlag == true && ChangeFlag == true) {
					Box[PreP] = ClickBox;
					ChangeFlag = false;
				}
				//���������ꏊ�ɓ��ꍞ�񂾏ꍇ�A���̈ʒu�ɖ߂�
				else if (isRelease(MOUSE_LBUTTON) && NotInFlag == false && Colli[Row * i + j].Dist < Radius / 2 && Row * i + j == PreP && ChangeFlag == true) {
					Box[PreP] = ClickBox;
					ChangeFlag = false;
				}

			}
		}

		//�z�[���h����߂���A�N���b�N�ێ����I���
		if (isRelease(MOUSE_LBUTTON)) {
			ClickBox = PawnsKind;
		}

		for (int i = 0; i < PawnsKind; i++) {//�I������ꏊ�̔���
			ClickColli[i].DistanceX = abs(ClickColli[i].Cx - MouseX);
			ClickColli[i].DistanceY = abs(ClickColli[i].Cy - MouseY);
			ClickColli[i].Dist = sqrt(ClickColli[i].DistanceX * ClickColli[i].DistanceX + ClickColli[i].DistanceY * ClickColli[i].DistanceY);
			//�͈͓��ɓ�������摜��剻
			if (ClickColli[i].Dist < Radius / 2) {
				ClickSize[i] = BigSize;
			}
			else {
				ClickSize[i] = DefaultSize;
			}
			//�z�[���h����Ă��āA�N���b�N�����ꏊ���͈͓��������ꍇ�@��̃z�[���h�J�n
			if (isPress(MOUSE_LBUTTON) && ClickColli[i].Dist < Radius / 2 && ClickBox == PawnsKind) {
				ClickBox = i;
			}
		}

	}

	void GAME::turnLapse() {
			ElapsedTurns++;
	}

	void GAME::filldJudg() {//�S�����܂��Ă邩�̔��� 
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
		//���𐔁E���S��v���E�s���S��v�������Z�b�g
		CorrectCnt = 0;
		PerfectCnt = 0;
		ImPerfectCnt = 0;
		SameKindCnt = 0;
		//���𐔂��J�E���g
			for (int i = 0; i < Row; i++) {
				if (Ans[i] == Box[Row * ElapsedTurns + i]) {
					CorrectCnt++;
				}
			}
			//�S�������Ă����ꍇ
			if (CorrectCnt == AnsCnt) {
				ClearFlag = true;
			}
			//�ꕔ�����������ꍇ
			else {
				for (int i = 0; i < Row; i++) {//���S��v���J�E���g
					if (Ans[i] == Box[Row * ElapsedTurns + i]) {
						PerfectCnt++;
					}
				}

				for (int i = 0; i < Row - 1; i++) {//�񓚂ɂ��Ԃ肪�����邩�𐔂���
						for (int j = i; j < Row; j++) {
							if (Box[Row * ElapsedTurns + i] == Box[Row * ElapsedTurns + j] && i != j) {//�𓚗p�̏ꏊ�ɓ����F���������ꍇ
								for (int k = 0; k < Row; k++) {
									if (Box[Row * ElapsedTurns + i] == Ans[k]) {//�����Ɖ񓚂ɓ����F���������ꍇ
										SameKindCnt++;
										break;
									}
								}
								break;
							}
						}
					}
				for (int i = 0; i < Row; i++) {//�s���S��v���J�E���g
					for (int j = 0; j < Row; j++) {
						if (Ans[i] == Box[Row * ElapsedTurns + j] && i != j) {
							ImPerfectCnt++;
						}
					}
				}
				if (ImPerfectCnt >= SameKindCnt) {
					ImPerfectCnt = ImPerfectCnt - SameKindCnt;//�s���S��v�Ƃ��Ԃ�̐��̍����o���B
				}
				for (int i = 0; i < Row; i++) {
					if (PerfectCnt > 0) {//���S��v���[����葽���ꍇ�̓q�b�g�̃s��������
						JudgeP[Row * ElapsedTurns + i] = AnsPerfect;
						PerfectCnt--;
					}
					else if (ImPerfectCnt > 0) {//�s���S��v�������ꍇ�A�u���[�̃s��������
						JudgeP[Row * ElapsedTurns + i] = AnsImPerfect;
						ImPerfectCnt--;
					}
					else {//�����Ƃ��O�������ꍇ�󔒂ɂ���
						JudgeP[Row * ElapsedTurns + i] = AnsSpace;
					}
				}
			}
		//�T�C�Y�����ׂăf�t�H���g�ɖ߂�
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
			text("������x���킵�悤!", width/2 - 630, 200);
			text("�X�y�[�X�L�[�Ń^�C�g���ɖ߂�", 100, 900);
		}
		else {
			text("congratulation!!", width / 2 - 500, 200);
			textSize(70);
			text(ElapsedTurns + 1, 660, 300);
			text("���Ȃ��́@�^�[���ŃN���A���܂����I", 350, 300);
			textSize(125);
			text("�X�y�[�X�L�[�Ń^�C�g���ɖ߂�", 100 , 900);
		}
		//�^�C�g����
		if (isTrigger(KEY_SPACE)) {
			State = TITLE;
		}
	}

/*
	int GAME::create()
	{
		//�����ł͎�ɉ摜�Ɖ��f�[�^��ǂݍ���

		//�����l�ݒ��Init()�֐��Ȃǂ�����Ă����ōs�����ق����ǂ��B
		//�V���v���ȃQ�[���Ȃ玟�̂悤�ɁA�����ōs���Ă��悢�B
		Px = width / 2;
		Py = height / 2;
		Radius = 200;

		return 0;
	}

	void GAME::destroy()
	{
		//create()��new�����ꍇ�͂�����delete���邱��
	}

	void GAME::proc()
	{
		//�����̓��C�����[�v����Ăяo����Ă���!!!!!

		//�`��--------------------------------------------------
		clear(255, 255, 255);
		//�~
		strokeWeight(50);
		stroke(0);
		fill(255, 0, 0);
		circle(Px, Py, Radius * 2);
		//�e�L�X�g���
		fill(0);
		textSize(100);
		print(Mx);
		text("Enter�Ń��j���[�ɖ߂�", 0, height);
		print(10);
		//���˂Ɣ����̐؂�ւ�
		if (isTrigger(MOUSE_LBUTTON)) {
			changeFlag = false;
			Px = Width / 2;
			Py = height / 2;
			if (Mx <= 0) {//�����AX���}�C�i�X���ɓ����ꍇ�́@�v���X�ɖ߂�
				Mx *= -1;
			}
		}
		if (isTrigger(MOUSE_RBUTTON)) {
			changeFlag = true;
			Px = Width / 2;
			Py = height / 2;
		}

		if (changeFlag == false) {//����
			Px += Mx;
			if (Px >= width + Radius + 50) {
				Px = 0 - Radius - 50;
			}
		}

		if (changeFlag == true) {//����
			Px += Mx;
			Py += My;
			if (Px + Radius>= width || Px - Radius<= 0) {
				Mx *= -1;
			}
			if (Py + Radius>= height || Py - Radius<= 0) {
				My *= -1;
			}
		}
		//���j���[�ɖ߂�------------------------------------------
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
	*/
}