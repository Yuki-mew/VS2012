#include "DxLib.h"
#include "stdlib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "fps.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	ChangeWindowMode(TRUE);		//ウィンドウモードに設定

	if( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);	//描写先を裏画面に設定
	SetGraphMode( 640 , 480 , 32 ) ;		//	ウィンドウサイズを	640*480	に設定

	SceneMgr_Initialize();

	while( (ScreenFlip()==0) && (ProcessMessage()==0) && (ClearDrawScreen()==0) )
	{		//表画面に画像を表示、メッセージ処理、画面クリア

		FpsUpdate();
		Keyboard_Update();
		SceneMgr_Update();
		SceneMgr_Draw();
		FpsDraw();
		FpsWait();
	}

	SceneMgr_Finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
 }