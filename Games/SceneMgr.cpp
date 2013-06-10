#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "SceneMgr.h"

static eScene mScene = eScene_Menu;		//シーン管理用の変数
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

	switch(mScene)		//シーンによって処理を分岐
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
	switch(mScene)		//シーンによって処理を分岐
	{
	case eScene_Menu:		//現在の画面がメニュー画面ならば
		Menu_Draw();			//メニュー画面の描画処理をする
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