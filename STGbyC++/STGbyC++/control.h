#pragma once
#include "player.h"
#include "back.h"
#include "enemy.h"

class CONTROL{

	//プレイヤークラス
	PLAYER *player;

	//背景クラス
	BACK *back;

	//敵クラス
	ENEMY *enemy[ENEMY_NUM];

private:
	CONTROL();
	~CONTROL();
public:
	void All();
	void GetPlayerPosition(double *x,double *y);
	void GetEnemyPosition(int index,double *x,double *y);
	static CONTROL &GetInstance(){
		static CONTROL control;
		return control;
	}
};

