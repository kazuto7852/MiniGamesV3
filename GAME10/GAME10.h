#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME10
{
    class GAME :public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void title();
            void init();
        void stage();
        void drawDesign();
        void setTimeColli();
        void drawTbutton();//buttonの描画
        void timeLaps();//時間経過
        void pawnsDraw();//駒の描写
        void collision();//設置判定用
        void turnLapse();//ターン経過用
        void filldJudg();//全部埋まってるかの判定用
        void judgment();//正解判定用
        void result();
        void destroy();
    private:
        enum STATE {//シーン変更用
            TITLE,
            STAGE,
            RESULT
        };
        enum KOMA {//駒判定用
            Red,
            Blue,
            Green,
            Yellow,
            Pink,
            White,
            Space
        };
        enum JUDGE {//ヒット・ブローの判定用
            AnsPerfect,
            AnsImPerfect,
            AnsSpace
        };
        struct JUDGEPAWNS {//判定用コマの画像を入れる場所
            int AnsPerfect,
                AnsImPerfect,
                AnsSpace;
        };
        struct PAWNS {//コマの画像を入れる場所
            int RedP,
                BlueP,
                GreenP,
                YellowP,
                PinkP,
                WhiteP,
                SpaceP;
        };
        STATE State;
        KOMA Koma;
        JUDGE Judge;
        JUDGEPAWNS JudgePawns;
        PAWNS Pawns;
        const int Row = 4;//行数
        const int Col = 8;//列数
        const int AnsCnt = 4;//答えの数
        int* Box = nullptr;//設置用の駒を入れる場所
        int* Click = nullptr;//選択用の駒を入れる場所
        int* Ans = nullptr;//答え用の駒を入れる場所
        int* JudgeP = nullptr;//ジャッチメント用の駒を入れる場所
        float* BoxSize = nullptr;//設置する場所の画像サイズを入れる場所
        float* ClickSize = nullptr;//選択する場所の画像サイズを入れる場所
        //title・stage・resultの画像
        int TitleImg = 0;
        int StageImg = 0;
        int ResultImg = 0;
        //効果音
            //title中の効果音
            int SelectSound = 0;
            bool VoiceFlag = false;//一回だけなるようにするためのフラッグ
            int PushSound = 0;
            //stage中の効果音
            int SetSound = 0;
            int JudgeSound = 0;
            //result中の効果音
            int ClearSound = 0;
            int OverSound = 0;
        //ステージのイメージ
            int SCntImage = 0;//制限時間表示用
            int SCx = 1650;
            int SCy = 150;
            int Smx = 25;
            int TCntImage = 0;//経過ターン表示用
            int TCx = 1650;
            int TCy = 950;
        //音楽
            int Bgm = 0;
        //サイズ変更用の変数
            float DefaultSize = 1.0f;
            float BigSize = 1.3f;
        //clickしたときの色保管場所
            int ClickBox = 0;
            int PawnsKind = 6;
        //設置する場所の位置指定用
            int Px = 150;
            int Py = 270;
            int Mx = 190;
            int My = 175;
            //設置する場所内で駒を変更するときに使う変数
                int PreP = 0;//移動前の場所を保存
                int TempP = 0;
                bool ChangeFlag = false;
                //元居た位置に戻すための変数たち
                bool NotInFlag = false;
            //設置する場所のデザインイメージ
                int Ipx = 150;
                int IPy = 530;
                int Imx = 190;
                int stageSetImg = 0;
        //選択用の駒配置指定
            int Kpx = 525;
            int Kpy = 970;
            int Kmx = 175;
        //答えの配置
            int Apx = 1700;
            int Apy = 250;
            int Amx = 175;
            int Amy = 175;
        //ジャッチメント用の配置(オレンジと白のやつ)
            int Jpx = 130;
            int Jpy = 100;
            int Jmmx = 35;//小さい左右の動き
            int Jmy = 40;//高低の動き
            int Jbmx = 190;//大きい左右の動き
        //正解判定用
            int CorrectCnt = 0;//正解数
            bool ClearFlag = false;//クリアフラッグ
            int PerfectCnt = 0;//完全一致
            int ImPerfectCnt = 0;//不完全一致
            int SameKindCnt = 0;//かぶり数
        //判定用
            struct COLLISION {
            int Cx;
            int Cy;
            int DistanceX;
            int DistanceY;
            int Dist;//最終的に離れている距離
        };
            COLLISION* Colli;//設置当たり判定
            COLLISION* ClickColli;//選択当たり判定
        int Radius = 150;
        int MaxTrun = 8;//最大ターン
        int ElapsedTurns = 0;//経過ターン
        bool FilldFlag = false;//全部埋まってるか埋まってないかの判定
        int MaxFilld = 4;//埋まる数の最大
        int FilldCnt = 0;//埋まってる数のカウント
        //時間設定用
        int DefaultTime = 20;//これに掛けていく
        int SetTime = 0;//時間を入れ込むための変数
        int SumTime = 0;//合計時間
        int TempTime = 0;
        bool DecisionFlag = false;
        struct TIME {
            int Tpx;
            int Tpy;
            int DistanceX;
            int DistanceY;
            int Dist;
            float Tscale;
            int TimeDecision;
        };
        int Tradius = 200;
        TIME* Time;
        int TimeButton[4];
        int TimeKind = 4;
        int Otpx = 400;
        int Otpy = 800;
        int Tmx = 350;
        int Flame = 60;
    };
}
