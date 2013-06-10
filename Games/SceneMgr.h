#ifndef SCENE_MGR_H

#define SCENE_MGR_H

typedef enum {
	eScene_Menu,
	eScene_Game,
	eScene_Config,

	eScene_None,
} eScene;

void SceneMgr_Initialize();	//初期化
void SceneMgr_Finalize();	//終了処理
void SceneMgr_Update();
void SceneMgr_Draw();

void SceneMgr_ChangeScene( eScene NextScene );		// 引数NextScene にシーンを変更する

#endif