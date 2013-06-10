#include "DxLib.h"
#include "stdlib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "fps.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	ChangeWindowMode(TRUE);		//�E�B���h�E���[�h�ɐݒ�

	if( DxLib_Init() == -1 )		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);	//�`�ʐ�𗠉�ʂɐݒ�
	SetGraphMode( 640 , 480 , 32 ) ;		//	�E�B���h�E�T�C�Y��	640*480	�ɐݒ�

	SceneMgr_Initialize();

	while( (ScreenFlip()==0) && (ProcessMessage()==0) && (ClearDrawScreen()==0) )
	{		//�\��ʂɉ摜��\���A���b�Z�[�W�����A��ʃN���A

		FpsUpdate();
		Keyboard_Update();
		SceneMgr_Update();
		SceneMgr_Draw();
		FpsDraw();
		FpsWait();
	}

	SceneMgr_Finalize();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
 }