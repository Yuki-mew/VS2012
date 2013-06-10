#include "DxLib.h"
#include "Game.h"
#include "GameResult.h"

static int IH_Result[3];

void GR_Initialize()
{
	LoadDivGraph( "images/BattleResult.png", 3, 1, 3, 640, 200, IH_Result  );
}

void GR_Finalize()
{
	for( int i=0; i<3; i++ )
	{
		DeleteGraph( IH_Result[i] );
	}
}

			//最終バトルの結果を表示
void GR_GameResult(){
	if (B_HP <= 0)
	{
		DrawGraph( 0, 100, IH_Result[0], FALSE );
		DrawFormatString( 300, 240, GetColor( 255, 255, 255 ), "Push Enter" );
		WaitKey();
		CheckGameStart = 7;
	} else if (A_HP <= 0){
		DrawGraph( 0, 100, IH_Result[2], FALSE );
		DrawFormatString( 300, 240, GetColor( 255, 255, 255 ), "Push Enter" );
		WaitKey();
		CheckGameStart = 7;
	} else if(attA==0 && defA==0 && techA==0)
	{
		if(A_HP == B_HP)
		{
			DrawGraph( 0, 100, IH_Result[1], FALSE );
			DrawFormatString( 300, 240, GetColor( 255, 255, 255 ), "Push Enter" );
			WaitKey();
			CheckGameStart = 7;
		} else if(A_HP > B_HP){
			DrawGraph( 0, 100, IH_Result[0], FALSE );
			DrawFormatString( 300, 240, GetColor( 255, 255, 255 ), "Push Enter" );
			WaitKey();
			CheckGameStart = 7;
		} else {
			DrawGraph( 0, 100, IH_Result[2], FALSE );
			DrawFormatString( 300, 240, GetColor( 255, 255, 255 ), "Push Enter" );
			WaitKey();
			CheckGameStart = 7;
		}
	} else {
		CheckGameStart = 1;
	}
}