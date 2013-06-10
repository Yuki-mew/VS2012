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
		NowSelect = ( NowSelect + 1 ) % eMenu_Num;		//�I���������
	}
	if( Keyboard_Get( KEY_INPUT_UP ) == 1 )
	{
		NowSelect = ( NowSelect + ( eMenu_Num - 1 ) ) % eMenu_Num;		//�V�[����ݒ��ʂɕύX
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
    DrawString(200, 150,     "���j���[��ʂł��B",GetColor(255,255,255));
    DrawString(200, 170,     "�㉺�L�[�������A�G���^�[�������ĉ������B",GetColor(255,255,255));
    DrawString(280, GAME_Y,  "�Q�[��",GetColor(255,255,255));
    DrawString(280, CONFIG_Y,"�V�ѕ�",GetColor(255,255,255));
    int y=0;
    switch(NowSelect){//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_Game://�Q�[���I�𒆂Ȃ�
        y=GAME_Y;    //�Q�[���̍��W���i�[
        break;
    case eMenu_Config://�ݒ�I�𒆂Ȃ�
        y=CONFIG_Y;    //�ݒ�̍��W���i�[
        break;
    }
    DrawString(250, y, "��", GetColor(255,255,255));
}