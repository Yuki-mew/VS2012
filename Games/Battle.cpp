#include "DxLib.h"
#include "Game.h"
#include "Battle.h"

Card card[3]= {
	{0, "Attack", 6, 2},
	{1, "Defence", 2, 6},
	{2, "Technique", 4, 4}
};

static int IH_Num[13];
static int IH_BattleResultBack;
static int IH_Mark[3];

static int Alpha = 0;
static int Alpha02 = 250;
static int Dam, Adice, Bdice, Adam, Bdam;
static int Mark_x = 0;
static int Mark_y = 140;


			//諸々の関数初期化&イメージハンドル生成
void Battle_Initialize()
{
	LoadDivGraph( "images/Number.png", 13, 13, 1, 58, 100, IH_Num );
	IH_BattleResultBack = LoadGraph( "images/BattleBack.png" );
	LoadDivGraph( "images/Marks.png", 3, 3, 1, 180, 180, IH_Mark );
}

			//イメージハンドル開放
void Battle_Finalize()		
{
	for( int i=0; i<13; i++ )
	{
		DeleteGraph( IH_Num[ i ] );
	}
	DeleteGraph( IH_BattleResultBack );
}

void DamageNum_Draw( int A, int B )
{
	switch(card[A].num)
	{
	case 0:			//Aが「Attack」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ 引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ 0 ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ 0 ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 1:		//Bが「Defence」　＝　Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 2:		//Bが「Technique」　＝　Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
	break;

	case 1:			//Aが「Defence」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 1:		//Bが「Defence」　＝　引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ 0 ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ 0 ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 2:		//Bが「Technique」　＝　Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
	break;

	case 2:			//Aが「Technique」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 1:		//Bが「Defence」　＝　Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 2:		//Bが「Technique」　＝　引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ 0 ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ 0 ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
		break;
	}

/*
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
	DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A]. ], FALSE );
	DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B]. ], FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
*/
	if( Alpha < 200 )
	{
		Alpha = Alpha + 20;
	} else {
		Parallel = 1;
		CheckCardFlash = 2;
	}
}

void DamageNum( int A, int B )
{
	switch(card[A].num)
	{
	case 0:			//Aが「Attack」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ 引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 1:		//Bが「Defence」　＝　Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 2:		//Bが「Technique」　＝　Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
	break;

	case 1:			//Aが「Defence」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 1:		//Bが「Defence」　＝　引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 2:		//Bが「Technique」　＝　Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
	break;

	case 2:			//Aが「Technique」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 1:		//Bが「Defence」　＝　Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 2:		//Bが「Technique」　＝　引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha02 );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
		
		break;
	}

	if( Parallel == 5 )
	{
		if( Alpha02 > 0 )
		{
			Alpha02 = Alpha02 - 25;
			Alpha = 0;
		} else {
			CheckCardFlash = 3;
		}
	}

}

void MaxDamageNum( int A, int B, int ADice, int BDice )
{
	switch(card[A].num)
	{
	case 0:			//Aが「Attack」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ 引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 1:		//Bが「Defence」　＝　Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 2:		//Bが「Technique」　＝　Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
	break;

	case 1:			//Aが「Defence」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;

		case 1:		//Bが「Defence」　＝　引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 2:		//Bが「Technique」　＝　Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
	break;

	case 2:			//Aが「Technique」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの負け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].def + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 1:		//Bが「Defence」　＝　Aの勝ち
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].def + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		case 2:		//Bが「Technique」　＝　引き分け
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, Alpha );
			DrawRotaGraph( 250, 300, 1.0, 0.0, IH_Num[ card[A].str + ADice ], FALSE );
			DrawRotaGraph( 250, 100, 1.0, 0.0, IH_Num[ card[B].str + BDice ], FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			break;
		}
		break;
	}
	
	if( Alpha < 250 )
	{
		Alpha = Alpha + 20;
	} else {
		Alpha02 = 250;
	}
}
/*
			//調整中　ダメージ結果の表示　whoの値で勝ち負け相打ち追撃すべてをやるかどうか考え中
void BattleResultDraw(int who, int Dam ){
	switch( who )
	{
	case 0:	//文字画像「あなたに」
		DrawGraph( 150, 160, IH_Play, TRUE );
		break;
	case 1: //文字画像「CPUに」
		DrawGraph( 150, 160, IH_CPU, TRUE );
		break;
	}
	DrawGraph( 200, 200, IH_Num[ Dam ], TRUE );
	DrawGraph( 250, 240, IH_Dam, TRUE );	//文字画像「のダメージ」

				//追撃が発生する場合
	if( Dam == 0 )
	{
		DrawGraph( 200, 200, IH_AddDam, TRUE );	//文字画像「追・撃」
		switch( who )
		{
		case 0:
			DrawGraph( 150, 160, IH_Play, TRUE );	//文字画像「あなたに」
			break;
		case 1:
			DrawGraph( 150, 160, IH_CPU, TRUE );	//文字画像「CPUに」
			break;
		}
		DrawGraph( 200, 200, IH_Num[ Dam ], TRUE );
		DrawGraph( 250, 240, IH_Dam, TRUE );	//文字画像「のダメージ」
	}
}
*/
			//バトル結果の計算
void Battle_Calculate(int A, int B, int A_Random, int B_Random)
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 200 );
	DrawGraph( 0, 150, IH_BattleResultBack, FALSE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	switch(card[A].num)
	{
	case 0:			//Aが「Attack」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ 引き分け
				DrawGraph( Mark_x, Mark_y, IH_Mark[0], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "引き分けです。\n");			
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの攻撃力:%d\n", A_Random);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの攻撃力:%d\n", B_Random);
				//相打ち相互ダメージ
			A_HP -= B_Random;
			B_HP -= A_Random;

			DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUに%dのダメージ\n", A_Random );
			DrawFormatString( 200, 280, GetColor(255, 255, 255), "あなたに%dのダメージ\n", B_Random );
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		case 1:		//Bが「Defence」　＝　Aの負け
				DrawGraph( Mark_x, Mark_y, IH_Mark[1], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "あなたの負けです。\n");
			Adam = card[A].def + A_Random;
			Bdam = card[B].str + B_Random;
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの防御力:%d\n", Adam);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの攻撃力:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "あなたに%dのダメージ\n", Dam);
				A_HP -= Dam;
			} else {
				A_HP -= card[B].str;
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUの追撃！！\n");
				DrawFormatString( 200, 280, GetColor(255, 255, 255), "あなたに%dのダメージ\n", card[B].str);
			}
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		case 2:		//Bが「Technique」　＝　Aの勝ち
				DrawGraph( Mark_x, Mark_y, IH_Mark[0], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "あなたの勝ちです。\n");
			Adam = card[A].str + A_Random;
			Bdam = card[B].def + B_Random;
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの攻撃力:%d\n", Adam);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの防御力:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUに%dのダメージ\n", Dam);
				B_HP -= Dam;
			} else {
				B_HP -= card[A].str;
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "あなたの追撃！！\n");
				DrawFormatString( 200, 280, GetColor(255, 255, 255), "CPUに%dのダメージ\n", card[A].str );
			}
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		}
	break;

	case 1:			//Aが「Defence」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの勝ち
				DrawGraph( Mark_x, Mark_y, IH_Mark[1], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "あなたの勝ちです。\n");
			Adam = card[A].str + A_Random;
			Bdam = card[B].def + B_Random;
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの攻撃力:%d\n", Adam);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの防御力:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUに%dのダメージ\n", Dam);
				B_HP -= Dam;
			} else {
				B_HP -= card[A].str;
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "あなたの追撃！！\n");
				DrawFormatString( 200, 280, GetColor(255, 255, 255), "CPUに%dのダメージ\n", card[A].str );
			}
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		case 1:		//Bが「Defence」　＝　引き分け
				DrawGraph( Mark_x, Mark_y, IH_Mark[1], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "引き分けです。\n");
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの攻撃力:%d\n", A_Random);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの攻撃力:%d\n", B_Random);
					//相打ち相互ダメージ
			A_HP -= B_Random;
			B_HP -= A_Random;

			DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUに%dのダメージ\n", A_Random);
			DrawFormatString( 200, 280, GetColor(255, 255, 255), "あなたに%dのダメージ\n", B_Random);
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		case 2:		//Bが「Technique」　＝　Aの負け
				DrawGraph( Mark_x, Mark_y, IH_Mark[3], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "あなたの負けです。\n");
			Adam = card[A].def + A_Random;
			Bdam = card[B].str + B_Random;
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの防御力:%d\n", Adam);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの攻撃力:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "あなたに%dのダメージ\n", Dam);
				A_HP -= Dam;
			} else {
				A_HP -= card[B].str;
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUの追撃！！\n");
				DrawFormatString( 200, 280, GetColor(255, 255, 255), "あなたに%dのダメージ\n", card[B].str );
			}
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		}
	break;

	case 2:			//Aが「Technique」
		switch(card[B].num){
		case 0:		//Bが「Attack」 ＝ Aの負け
				DrawGraph( Mark_x, Mark_y, IH_Mark[1], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "あなたの負けです。\n");
			Adam = card[A].def + A_Random;
			Bdam = card[B].str + B_Random;
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの防御力:%d\n", Adam);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの攻撃力:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "あなたに%dのダメージ\n", Dam);
				A_HP -= Dam;
			} else {
				A_HP -= card[B].str;
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUの追撃！！\n");
				DrawFormatString( 200, 280, GetColor(255, 255, 255), "あなたに%dのダメージ\n", card[B].str );
			}
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
			break;
		case 1:		//Bが「Defence」　＝　Aの勝ち
				DrawGraph( Mark_x, Mark_y, IH_Mark[2], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "あなたの勝ちです。\n");
			Adam = card[A].str + A_Random;
			Bdam = card[B].def + B_Random;
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの攻撃力:%d\n", Adam);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの防御力:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUに%dのダメージ\n", Dam);
				B_HP -= Dam;
			} else {
				B_HP -= card[A].str;
				DrawFormatString( 200, 260, GetColor(255, 255, 255), "あなたの追撃！！\n");
				DrawFormatString( 200, 280, GetColor(255, 255, 255), "CPUに%dのダメージ\n", card[A].str );
			}
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		case 2:		//Bが「Technique」　＝　引き分け
				DrawGraph( Mark_x, Mark_y, IH_Mark[2], TRUE );
			DrawFormatString( 200, 180, GetColor(255, 255, 255), "引き分けです。\n");
			DrawFormatString( 200, 200, GetColor(255, 255, 255), "あなたの攻撃力/防御力:%d\n", A_Random);
			DrawFormatString( 200, 220, GetColor(255, 255, 255), "CPUの攻撃力/防御力:%d\n", B_Random);

			A_HP -= B_Random;
			B_HP -= A_Random;

			DrawFormatString( 200, 260, GetColor(255, 255, 255), "CPUに%dのダメージ\n", A_Random );
			DrawFormatString( 200, 280, GetColor(255, 255, 255), "あなたに%dのダメージ\n", B_Random );
			DrawFormatString( 200, 300, GetColor( 255, 255, 255 ), "Push Enter" );
		break;
		}
	break;
	}
	Alpha = 0;
}