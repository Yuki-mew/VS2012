#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "SceneMgr.h"

static eScene mScene = eScene_Menu;		//�V�[���Ǘ��p�̕ϐ�
static eScene mNextScene = eScene_None;

static void SceneMgr_InitializeModule( eScene scene );
static void SceneMgr_FinalizeModule( eScene scene );

void SceneMgr_Initialize()
{
	SceneMgr_InitializeModule( mScene );
}

void SceneMgr_Finalize()
{
	SceneMgr_FinalizeModule( mScene );
}

void SceneMgr_Update()
{
	if(mNextScene != eScene_None){
		SceneMgr_FinalizeModule(mScene);
		mScene = mNextScene;
		mNextScene = eScene_None;
		SceneMgr_InitializeModule( mScene );
	}

	switch(mScene)		//�V�[���ɂ���ď����𕪊�
	{
	case eScene_Menu:
		Menu_Update();
		break;
	case eScene_Game:
		Game_Update();
		break;
	case eScene_Config:
		Config_Update();
		break;
	}
}

void SceneMgr_Draw()
{
	switch(mScene)		//�V�[���ɂ���ď����𕪊�
	{
	case eScene_Menu:		//���݂̉�ʂ����j���[��ʂȂ��
		Menu_Draw();			//���j���[��ʂ̕`�揈��������
		break;
	case eScene_Game:
		Game_Draw();
		break;
	case eScene_Config:
		Config_Draw();
		break;
	}
}

void SceneMgr_ChangeScene( eScene NextScene )
{
	mNextScene = NextScene;
}

static void SceneMgr_InitializeModule( eScene scene )
{
	switch(scene)
	{
	case eScene_Menu:
		Menu_Initialize();
		break;
	case eScene_Game:
		Game_Initialize();
		break;
	case eScene_Config:
		Config_Initialize();
		break;
	}
}

static void SceneMgr_FinalizeModule( eScene scene )
{
	switch(scene)
	{
	case eScene_Menu:
		Menu_Finalize();
		break;
	case eScene_Game:
		Game_Finalize();
		break;
	case eScene_Config:
		Config_Finalize();
		break;
	}
}