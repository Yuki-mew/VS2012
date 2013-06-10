#include "Config.h"
#include "SceneMgr.h"
#include "DxLib.h"

static int mImageHandle;

void Config_Initialize()
{
	mImageHandle = LoadGraph("images/Scene_Config.png");
}

void Config_Finalize()
{
	DeleteGraph( mImageHandle );
}

void Config_Update()
{
	if( CheckHitKey( KEY_INPUT_ESCAPE ) ){
		SceneMgr_ChangeScene(eScene_Menu);
	}
}

void Config_Draw()
{
	DrawGraph( 0, 0, mImageHandle, FALSE );
	DrawString( 0, 0, "設定画面です。", GetColor(255, 0, 0) );
	DrawString( 0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 0, 0) );
}