#pragma once
#include "player.h"
#include "back.h"
#include "enemy.h"

class CONTROL{

	//�v���C���[�N���X
	PLAYER *player;

	//�w�i�N���X
	BACK *back;

	//�G�N���X
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

