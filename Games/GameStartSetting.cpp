#include "DxLib.h"
#include "CardSetting.h"
#include "Game.h"

static int IH_StatusBar;
static int IH_GameStart_CutIn;
static int IH_HP_Bar;
static int IH_HP_Blind;

static int SB_x;
static int GS_x;

		//イメージハンドルを読み込み
void GSS_Initialize()
{
	SB_x = 640;
	GS_x = 640;
	IH_StatusBar = LoadGraph("images/StatusBar_1.png");
	IH_GameStart_CutIn = LoadGraph("images/CutIn.png");
	IH_HP_Bar = LoadGraph( "images/HP_Bar.png" );
	IH_HP_Blind = LoadGraph( "images/HP_Blind.png" );
}

		//イメージハンドルのメモリ解放
void GSS_Finalize()
{
	DeleteGraph( IH_StatusBar );
	DeleteGraph( IH_GameStart_CutIn );
	DeleteGraph( IH_HP_Bar );
	DeleteGraph( IH_HP_Blind );
}

		//ゲーム開始のスライドイン表示&計算
void GSS_GameStart_Draw()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );
	DrawGraph( GS_x, 160, IH_GameStart_CutIn, FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	if( GS_x>0 )
	{
		GS_x = GS_x - 40;
	} else {
		WaitKey();
		CheckGameStart = 1;
//		GS_x = 640;
	}
}

		//ステータスバー背景の計算
void GSS_StatusBar_Upload()
{
	if( SB_x > 500 )
	{
		SB_x = SB_x - 20;
	}
}

		//ステータスバー背景の表示
void GSS_StatusBar_Draw()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 158 );
	DrawGraph( SB_x, 0, IH_StatusBar, FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
}

		//ステータス詳細(文字)の表示
void GSS_Status_Draw()
{
	if( SB_x == 500 )
	{
		DrawFormatString( 510, 10 , GetColor( 255, 255, 255 ), "HP = [%d / 25]", B_HP);
		DrawGraph( 510, 35, IH_HP_Bar, FALSE );
		DrawRotaGraph3( 510+1 + 117, 35+1 + 17, 0, 0, 1.0 - (float)B_HP / 25.0, 1.0, PI, IH_HP_Blind, FALSE );

		DrawRotaGraph( 530, 100, 0.3, 0.0, IH_Card[0], FALSE );
		DrawRotaGraph( 530 + 40, 100, 0.3, 0.0, IH_Card[1], FALSE );
		DrawRotaGraph( 530 + 80, 100, 0.3, 0.0, IH_Card[2], FALSE );

		DrawFormatString( 515 + 3, 130 , GetColor( 255, 255, 255 ), "[%d]", attB);
		DrawFormatString( 515 + 43, 130 , GetColor( 255, 255, 255 ), "[%d]", defB);
		DrawFormatString( 515 + 83, 130 , GetColor( 255, 255, 255 ), "[%d]", techB);
				//ここまで敵のステータス

		DrawRotaGraph( 530, 360, 0.3, 0.0, IH_Card[0], FALSE );
		DrawRotaGraph( 530 + 40, 360, 0.3, 0.0, IH_Card[1], FALSE );
		DrawRotaGraph( 530 + 80, 360, 0.3, 0.0, IH_Card[2], FALSE );

		DrawFormatString( 515 + 3, 390 , GetColor( 255, 255, 255 ), "[%d]", attA);
		DrawFormatString( 515 + 43, 390 , GetColor( 255, 255, 255 ), "[%d]", defA);
		DrawFormatString( 515 + 83, 390 , GetColor( 255, 255, 255 ), "[%d]", techA);

		DrawFormatString( 510, 420 , GetColor( 255, 255, 255 ), "HP = [%d / 25]", A_HP);
		DrawGraph( 510, 445, IH_HP_Bar, FALSE );
		DrawRotaGraph3( 510+1 + 117 , 445+1 + 17, 0, 0, 1.0 - (float)A_HP / 25.0, 1.0, PI, IH_HP_Blind, FALSE );
				//ここまで自分のステータス
	}
}