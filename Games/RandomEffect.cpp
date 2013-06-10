#include "DxLib.h"
#include "Game.h"
#include "RandomEffect.h"
#include "Keyboard.h"

static int IH_DiceBack;
static int IH_Dice[9];


static int dice_ex = 640;
static int X_SIZE=100;
static int Y_SIZE=100;
static int DiceStopTemp;
static int EffectCounter = 0;

static int ALPHA_Temp = 150;
static int ADD_Temp = 150;
static double BigDice = 1.0;

static int Move_x = 50 + 50;
static int Move_y = 280;
static int Move_ex = 50 + 50 + 300;
static int Move_ey = 280;


static int counter;

void RE_Initialize()
{
	IH_DiceBack = LoadGraph( "images/background1.png" );
	LoadDivGraph( "images/Dice.png", 9, 9, 1, X_SIZE, Y_SIZE, IH_Dice );
}

void RE_Finalize()
{
	DeleteGraph( IH_DiceBack );

	for( int i=0; i<9; i++ )
	{
		DeleteGraph( IH_Dice[ i ] );
	}
}

//ランダムダイスの計算
int RE_BattleRandomDice( int CardNum )
{
	if( CardNum == 2)
	{
		return GetRand(8);
	} else {
		return GetRand(4);
	}
}

			//ランダムダイスフィールドの表示	CGS ==　４
void RE_BattleDiceEffect()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );
	DrawGraph( dice_ex, 140, IH_DiceBack, FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	if( dice_ex > 0 )
	{
		dice_ex = dice_ex - 40;
	} else {
			Parallel = 2;
	}
}

			//Enter押してダイスをストップ
void RE_DiceStop(){
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );
	DrawGraph( dice_ex, 140, IH_DiceBack, FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	DrawFormatString( 300, 400, GetColor( 255, 255, 255 ), "PushEnter    [ %d ]", EffectCounter );

	if( Keyboard_Get( KEY_INPUT_RETURN ) == 1 || ( EffectCounter == 400 ) )
	{
		Parallel = 3;
	} else {
		EffectCounter = EffectCounter + 1;
		DrawGraph( 50, 180, IH_Dice[ EffectCounter%9 ], FALSE );
		DrawGraph( 50 + 300, 180, IH_Dice[ (EffectCounter + 18)%9 ], FALSE );
	}
}

			//アルファ値をいじりながらダイス拡大エフェクト
void RE_DiceResult()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );
	DrawGraph( dice_ex, 140, IH_DiceBack, FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	DrawGraph( 50, 180, IH_Dice[ DiceTempA ], FALSE );
	DrawGraph( 50 + 300, 180, IH_Dice[ DiceTempB ], FALSE );

	if( ALPHA_Temp > 0 ){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, ALPHA_Temp );
		DrawRotaGraph( 50 + 50, 180 + 50, BigDice, 0.0, IH_Dice[ DiceTempA ], FALSE  );
		DrawRotaGraph( 50 + 50 + 300, 180 + 50, BigDice, 0.0, IH_Dice[ DiceTempB ], FALSE  );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		ALPHA_Temp = ALPHA_Temp - 15;
		BigDice = BigDice + 0.05;
	}

	if( Keyboard_Get( KEY_INPUT_RETURN ) == 1 )
	{
		Parallel = 4;
		ALPHA_Temp = 150;
		ADD_Temp = 150;
	}
}

			//ダイスの数字がカードの部分まで移動する
void RE_DiceMoveEffect()
{
//	SetDrawBlendMode( DX_BLENDMODE_ALPHA, ALPHA_Temp );
	DrawRotaGraph( Move_x, Move_y, 1.0, 0.0, IH_Dice[ DiceTempA ], FALSE );
	DrawRotaGraph( Move_ex, Move_ey, 1.0, 0.0, IH_Dice[ DiceTempB ], FALSE );
//	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	if( Move_x < 250 ){
		Move_x = Move_x + 10;
		Move_y = Move_y + 7;
		Move_ex = Move_ex - 10;
		Move_ey = Move_ey - 13;
	} else {
		Parallel = 5;
	}
}

void RE_DiceAlphaEffect()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, ALPHA_Temp );
	DrawRotaGraph( Move_x, Move_y, 1.0, 0.0, IH_Dice[ DiceTempA ], FALSE );
	DrawRotaGraph( Move_ex, Move_ey, 1.0, 0.0, IH_Dice[ DiceTempB ], FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	if( ALPHA_Temp > 0 ) {	
		ALPHA_Temp = ALPHA_Temp - 15;
	}

	if( Keyboard_Get( KEY_INPUT_RETURN ) == 1 )
	{
		Move_x = 50 + 50;
		Move_y = 280;
		Move_ex = 50 + 350;
		Move_ey = 280;

		EffectCounter = 0;
		ALPHA_Temp = 150;
		ADD_Temp = 150;
		BigDice = 1.0;
		dice_ex = 640;
		Parallel = 0;
		CheckGameStart = 5;
	}
}