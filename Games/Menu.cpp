#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Menu.h"
#include "keyboard.h"

const static int GAME_Y = 240;
const static int CONFIG_Y = 270;
static int mImageHandle;

typedef enum
{
	eMenu_Game,
	eMenu_Config,

	eMenu_Num,
} eMenu;

static int NowSelect = eMenu_Game;

void Menu_Initialize()
{
	mImageHandle = LoadGraph("images/Scene_Menu.png");
}

void Menu_Finalize()
{
	DeleteGraph( mImageHandle );
}

void Menu_Update()
{
	if( Keyboard_Get( KEY_INPUT_DOWN ) == 1 )
	{
		NowSelect = ( NowSelect + 1 ) % eMenu_Num;		//選択肢一つ下げ
	}
	if( Keyboard_Get( KEY_INPUT_UP ) == 1 )
	{
		NowSelect = ( NowSelect + ( eMenu_Num - 1 ) ) % eMenu_Num;		//シーンを設定画面に変更
	}
	if(Keyboard_Get(KEY_INPUT_RETURN) == 1)
	{
		switch( NowSelect )
		{
		case eMenu_Game:
			SceneMgr_ChangeScene( eScene_Game );
			break;
		case eMenu_Config:
			SceneMgr_ChangeScene( eScene_Config );
			break;
		}
	}
}

void Menu_Draw(){
	DrawGraph( 0, 0, mImageHandle, FALSE );
    DrawString(200, 150,     "メニュー画面です。",GetColor(255,255,255));
    DrawString(200, 170,     "上下キーを押し、エンターを押して下さい。",GetColor(255,255,255));
    DrawString(280, GAME_Y,  "ゲーム",GetColor(255,255,255));
    DrawString(280, CONFIG_Y,"遊び方",GetColor(255,255,255));
    int y=0;
    switch(NowSelect){//現在の選択状態に従って処理を分岐
    case eMenu_Game://ゲーム選択中なら
        y=GAME_Y;    //ゲームの座標を格納
        break;
    case eMenu_Config://設定選択中なら
        y=CONFIG_Y;    //設定の座標を格納
        break;
    }
    DrawString(250, y, "■", GetColor(255,255,255));
}