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
		DrawFormatString( 20, 40, GetColor( 255, 255, 255 ), " ���Ȃ���%d�̃J�[�h��I�����܂����B", A_Card );
		DrawFormatString( 20, 140, GetColor( 255, 255, 255 ), " CPU��%d�̃J�[�h��I�����܂����B", B_Card );
		FpsDraw();

		if( ( CheckGameStart >= 1 ) )
		{
			GSS_StatusBar_Upload();		//�X�e�[�^�X�o�[�̕\���ʒu���v�Z
			GSS_StatusBar_Draw();		//�X�e�[�^�X�o�[�̕\��
			GSS_Status_Draw();			//���X�e�[�^�X�̕\��
		}

		if( CheckGameStart == 0 )
		{
			GSS_GameStart_Draw();		//�h�Q�[���X�^�[�g�h���X���C�h�C��
		}
		
		if( CheckGameStart == 1 )
		{
			CS_CardSet();				//�J�[�h���X���C�h�C��
		}

		if( CheckGameStart == 2 )
		{
			Keyboard_Update();
			CS_CardPlace_Update();
			CS_DrawCard();					//�J�[�h�I�����
		}

		if( CheckGameStart == 3 )
		{
			CS_CardOutSide();		//�J�[�h����ʊO�ɃX���C�h�A�E�g
		}

		if( CheckGameStart == 4 )
		{
			// P0 - CCF1 - P1 - P2 - P3 - P4
			//CheckCardFlash 1 == �J�[�h���g�p����X�e�[�^�X���l���g��\��
			//Parallel 5 == �J�[�h���琔����I�o������
			//Parallel 1 == �o�b�N�_�C�X��\��
			//Parallel 2 == �_�C�X���~�߂�
			//Parallel 3 == �_�C�X���ʕ\��
			//Parallel 4 == �_�C�X�̈ړ�

			CS_SelectedCard_Draw( ACardTemp, BCardTemp );		//�I�������J�[�h���X���C�h�C��

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