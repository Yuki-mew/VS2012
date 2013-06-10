#include "DxLib.h"
#include "Keyboard.h"
#include "CardSetting.h"
#include "CountStock.h"
#include "Game.h"

int IH_Card[4];
int IH_Mark[3];
//static int IH_PicUp[10];

static int Enemy_x;
static int Enemy_y=-60;
static int Start_y=480;
static int SelectedCard = 0;
static int y[3] = { 260, 280, 280 };
static int sCard_y = 480 + 90;
static int esCard_y = -90;

static int Alpha = 0;
static double Roll = 0.0;
static double BigA = 1.0;
static double BigB = 0.9;

static double BigStatus = 1.0;

		//イメージハンドル分割ロード
void CS_Initialize()
{
//	SelectedCard = 0;
	LoadDivGraph( "images/Cards.png", 4, 4, 1, 120, 167, IH_Card );
	LoadDivGraph( "images/Marks.png", 3, 3, 1, 180, 180, IH_Mark );
//	LoadDivGraph( "images/Number.png", 10, 10, 1, 58, 100, IH_PicUp );
}

		//イメージハンドルのメモリ解放
void CS_Finalize()
{
	for(int i=0;i<4;i++)
	{
		DeleteGraph( IH_Card[ i ] );
	}
	
	for( int i=0; i<3; i++ )
	{
		DeleteGraph( IH_Mark[ i ] );
	}
}

		//カードがスライドイン
void CS_CardSet()
{
	Enemy_x = 110 + 10;
	for( int i=0; i<3; i++ ){
		DrawRotaGraph( Enemy_x, Enemy_y, 0.9, 0.0, IH_Card[3], FALSE );
		Enemy_x = Enemy_x + 100 + 30;
	}

	if( Enemy_y < 90 )
	{
		Enemy_y = Enemy_y + 15;
	}

	DrawGraph( 30, Start_y, IH_Card[0], FALSE );
	DrawGraph( 190, Start_y, IH_Card[1], FALSE );
	DrawGraph( 350, Start_y, IH_Card[2], FALSE );

	if( Start_y > 280 )
	{
		Start_y = Start_y - 15;
	} else {
		CheckGameStart = 2;
	}
}

		//カードの表示情報更新&[Enter]でカード選択（選択カードをずらして表示）	CGS ==　２
void CS_CardPlace_Update(){
	if( Keyboard_Get( KEY_INPUT_RIGHT ) == 1 )
	{
		SelectedCard = ( SelectedCard + 1 ) % eCard_Num;
	}
	if( Keyboard_Get( KEY_INPUT_LEFT ) == 1 )
	{
		SelectedCard = ( SelectedCard + ( eCard_Num - 1 ) ) % eCard_Num;
	}	

	if( Keyboard_Get( KEY_INPUT_RIGHT ) == 1  || Keyboard_Get( KEY_INPUT_LEFT ) == 1 )
	{
		for( int i=0; i<3; i++ ){
			if( SelectedCard == i )
			{
				y[i] = 260;
			} else {
				y[i] = 280;
			}
		}
	}

	if( Keyboard_Get( KEY_INPUT_RETURN ) == 1 )
	{
		A_Card = SelectedCard;

//ここから下は実験部分
//		B_Card = GetRand(2);
		ACardTemp = A_Card;
//		BCardTemp = B_Card;
		CountCardStock_A( A_Card );
	if( CheckGameStart != 1 )
	 {		//お試し
		while(1)
		{
			B_Card = GetRand( 2 );
//		DrawFormatString( 20, 60, GetColor( 255, 255, 255 ), " CPUは%dのカードを選択しました。", B_Card );
//		WaitKey();
			if( CheckCardStock_B( B_Card ) == 1 )
			{
				BCardTemp = B_Card;
				CountCardStock_B( B_Card );
			break;
			}
		}

//ここまで実験部分
//		DrawFormatString( 20, 60, GetColor( 255, 255, 255 ), " [ %d ]チェックゲームスタート", CheckGameStart );
//		WaitKey();

		CheckGameStart = 3;
	}
					} //お試し
}

		//カードの表示		CGS ==　２
void CS_DrawCard(){
	Enemy_x = 110 + 10;		//二回目以降のループのための初期化
	for( int i=0; i<3; i++ ){
		DrawRotaGraph( Enemy_x, Enemy_y, 0.9, 0.0, IH_Card[3], FALSE );
		Enemy_x = Enemy_x + 100 + 30;
	}

	DrawGraph( 30, y[0], IH_Card[0], FALSE );
	DrawGraph( 190, y[1], IH_Card[1], FALSE );
	DrawGraph( 350, y[2], IH_Card[2], FALSE );

			//デバック用データ
//	DrawFormatString( 20, 20, GetColor( 255, 255, 255 ), " カーソルは%dを選択しています。", SelectedCard );
//	DrawFormatString( 20, 40, GetColor( 255, 255, 255 ), " あなたは%dのカードを選択しました。", A_Card );
//	DrawFormatString( 20, 60, GetColor( 255, 255, 255 ), " CPUは%dのカードを選択しました。", B_Card );
//	DrawFormatString( 20, 100, GetColor( 255, 255, 255 ), " Y[0]=%d\n, Y[1]=%d\n, Y[2]=%d\n", y[0], y[1], y[2] );
}

		//カードがスライドアウト　CGS ==　３
void CS_CardOutSide()
{
	Enemy_x = 110 + 10;
	for( int i=0; i<3; i++ ){
		DrawRotaGraph( Enemy_x, Enemy_y, 0.9, 0.0, IH_Card[3], FALSE );
		Enemy_x = Enemy_x + 100 + 30;
	}

	if( Enemy_y > -90 )
	{
		Enemy_y = Enemy_y - 15;
	}

	DrawGraph( 30, Start_y, IH_Card[0], FALSE );
	DrawGraph( 190, Start_y, IH_Card[1], FALSE );
	DrawGraph( 350, Start_y, IH_Card[2], FALSE );

	if( Start_y < 480 )
	{
		Start_y = Start_y + 15;
	} else {
/*
//		B_Card = GetRand(2);
		ACardTemp = A_Card;
//		BCardTemp = B_Card;
		CountCardStock_A( A_Card );

		while(1)
		{
			B_Card = GetRand( 2 );
			if( CheckCardStock_B( B_Card ) == 1 )
			{
				CountCardStock_B( B_Card );

				break;
			}
		}

		BCardTemp = B_Card;
*/
		CheckGameStart = 4;
	}
}

		//選択したカードを表示	CGS ==　４　&&　ダイスを吸収した時拡大エフェクト
void CS_SelectedCard_Draw( int A_Card, int B_Card )
{


		switch( B_Card ){
	case 0:
		DrawRotaGraph( 250, esCard_y, 0.9, 0.0, IH_Card[0], FALSE );
		break;
	case 1:
		DrawRotaGraph( 250, esCard_y, 0.9, 0.0, IH_Card[1], FALSE );
		break;
	case 2:
		DrawRotaGraph( 250, esCard_y, 0.9, 0.0, IH_Card[2], FALSE );
		break;
	}

	switch( A_Card ){
	case 0:
		DrawRotaGraph( 190 + 60, sCard_y, 1.0, 0.0, IH_Card[0], FALSE );
		break;
	case 1:
		DrawRotaGraph( 190 + 60, sCard_y, 1.0, 0.0, IH_Card[1], FALSE );
		break;
	case 2:
		DrawRotaGraph( 190 + 60, sCard_y, 1.0, 0.0, IH_Card[2], FALSE );
		break;
	}




	if( ( Parallel == 5 ) && ( Alpha < 250 ) ){
		SetDrawBlendMode( DX_BLENDMODE_ADD, 250 );
	} else {
		BigA = 1.0;
		BigB = 0.9;
	}

	switch( B_Card ){
	case 0:
		DrawRotaGraph( 250, esCard_y, BigB, 0.0, IH_Card[0], FALSE );
		break;
	case 1:
		DrawRotaGraph( 250, esCard_y, BigB, 0.0, IH_Card[1], FALSE );
		break;
	case 2:
		DrawRotaGraph( 250, esCard_y, BigB, 0.0, IH_Card[2], FALSE );
		break;
	}

	if( esCard_y < 90 ){
		esCard_y = esCard_y + 20;
	}

	switch( A_Card ){
	case 0:
		DrawRotaGraph( 190 + 60, sCard_y, BigA, 0.0, IH_Card[0], FALSE );
		break;
	case 1:
		DrawRotaGraph( 190 + 60, sCard_y, BigA, 0.0, IH_Card[1], FALSE );
		break;
	case 2:
		DrawRotaGraph( 190 + 60, sCard_y, BigA, 0.0, IH_Card[2], FALSE );
		break;
	}

	if( Parallel == 5 )
	{
		if( Alpha < 250 )
		{
			BigA = BigA + 0.01;
			BigB = BigB + 0.01;
			Alpha = Alpha + 15;
		}
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
	}

	if( sCard_y > 280 + 90 )
	{
		sCard_y = sCard_y - 20;
	} else {
		if( Parallel == 0 ){
			CheckCardFlash = 1;
		}
	}
}

		//カード初期表示位置のリセット
void CS_CardPlaceReset()
{
	sCard_y = 480 + 90;
	esCard_y = -90;
	Alpha = 0;
}