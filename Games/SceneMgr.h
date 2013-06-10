#ifndef SCENE_MGR_H

#define SCENE_MGR_H

typedef enum {
	eScene_Menu,
	eScene_Game,
	eScene_Config,

	eScene_None,
} eScene;

void SceneMgr_Initialize();	//������
void SceneMgr_Finalize();	//�I������
void SceneMgr_Update();
void SceneMgr_Draw();

void SceneMgr_ChangeScene( eScene NextScene );		// ����NextScene �ɃV�[����ύX����

#endif