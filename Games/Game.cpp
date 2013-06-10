#include "Game.h"
#include "SceneMgr.h"
#include "Battle.h"
#include "GameStartSetting.h"
#include "CardSetting.h"
#include "CountStock.h"
#include "GameResult.h"
#include "RandomEffect.h"
#include "Keyboard.h"
#include "DxLib.h"
#include "fps.h"

static int mImageHandle;
static int mImageHandle1;

int CheckGameStart = 0;
int Parallel;
int CheckCardFlash = 0;
int A_HP = 25;
int B_HP = 25;
int A_Card = -1;
int B_Card = -1;
int ACardTemp = -1;
int BCardTemp = -1;
int DiceTempA;
int DiceTempB;
int attA, defA, techA;
int attB, defB, techB;

void Game_Initialize()
{
	mImageHandle = LoadGraph("images/Scene_Game.png");
	mImageHandle1 = LoadGraph("images/temp.png");

	Battle_Initialize();
	GSS_Initialize();
	CS_Initialize();
	RE_Initialize();
	GR_Initialize();

	CheckGameStart = 0;

	A_HP = 25;
	B_HP = 25;

	attA = 4;
	defA = 4;
	techA = 4;

	attB = 4;
	defB = 4;
	techB = 4;
}

void Game_Finalize()
{
	DeleteGraph( mImageHandle );
	DeleteGraph( mImageHandle1 );

	Battle_Finalize();
	GSS_Finalize();
	CS_Finalize();
	RE_Finalize();
	GR_Finalize();
}

void Game_Update()
{
	if( CheckHitKey( KEY_INPUT_ESCAPE )!=0 )
	{
		SceneMgr_ChangeScene( eScene_Menu );
	}
}

void Game_Draw()
{

	while( ( ScreenFlip()==0 ) && ( ProcessMessage()==0 ) && ( ClearDrawScreen()==0 ) )
	{
		FpsUpdate();
		DrawGraph( 0, 0, mImageHandle, FALSE );
		DrawFormatString( 0, 80, GetColor( 255, 255, 255 ), "CheckGeameStart=[ %d ]", CheckGameStart );
		DrawFormatString( 20, 40, GetColor( 255, 255, 255 ), " あなたは%dのカードを選択しました。", A_Card );
		DrawFormatString( 20, 140, GetColor( 255, 255, 255 ), " CPUは%dのカードを選択しました。", B_Card );
		FpsDraw();

		if( ( CheckGameStart >= 1 ) )
		{
			GSS_StatusBar_Upload();		//ステータスバーの表示位置を計算
			GSS_StatusBar_Draw();		//ステータスバーの表示
			GSS_Status_Draw();			//諸ステータスの表示
		}

		if( CheckGameStart == 0 )
		{
			GSS_GameStart_Draw();		//”ゲームスタート”がスライドイン
		}
		
		if( CheckGameStart == 1 )
		{
			CS_CardSet();				//カードがスライドイン
		}

		if( CheckGameStart == 2 )
		{
			Keyboard_Update();
			CS_CardPlace_Update();
			CS_DrawCard();					//カード選択画面
		}

		if( CheckGameStart == 3 )
		{
			CS_CardOutSide();		//カードが画面外にスライドアウト
		}

		if( CheckGameStart == 4 )
		{
			// P0 - CCF1 - P1 - P2 - P3 - P4
			//CheckCardFlash 1 == カードが使用するステータス数値を拡大表示
			//Parallel 5 == カードから数字を露出させる
			//Parallel 1 == バックダイスを表示
			//Parallel 2 == ダイスを止める
			//Parallel 3 == ダイス結果表示
			//Parallel 4 == ダイスの移動

			CS_SelectedCard_Draw( ACardTemp, BCardTemp );		//選択したカードがスライドイン

			if( CheckCardFlash == 1 )
			{
				DamageNum_Draw( ACardTemp, BCardTemp );
			} else if( CheckCardFlash == 2 ){
				DamageNum(ACardTemp, BCardTemp);
			} else if( CheckCardFlash == 3 ){
				MaxDamageNum( ACardTemp, BCardTemp, DiceTempA, DiceTempB );
			}

			if( Parallel == 1 )
			{
				DiceTempA = RE_BattleRandomDice( ACardTemp );
				DiceTempB = RE_BattleRandomDice( BCardTemp );
				RE_BattleDiceEffect();
			}

			if( Parallel == 2 )
			{
				Keyboard_Update();
				RE_DiceStop();
			}

			if( Parallel == 3 )
			{
				Keyboard_Update();
				RE_DiceResult();
			}

			if( Parallel == 4 )
			{
				RE_DiceMoveEffect();
			}

			if( Parallel == 5 )
			{
				Keyboard_Update();
				RE_DiceAlphaEffect();
			}
		}

		if( CheckGameStart == 5 )
		{
			CS_CardPlaceReset();

			Battle_Calculate(ACardTemp, BCardTemp , DiceTempA, DiceTempB );

			WaitKey();
			CheckGameStart = 6;
		}

		if( CheckGameStart == 6 )
		{
			CheckCardFlash = 0;
			DrawGraph( 0, 0, mImageHandle, FALSE );
			GR_GameResult();
		}

		if( CheckGameStart == 7 )
		{
			SceneMgr_ChangeScene( eScene_Menu );
			CheckGameStart = 8;
			break;
		}

		FpsWait();
	}

}