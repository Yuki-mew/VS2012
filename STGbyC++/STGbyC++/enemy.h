#pragma once
#include "pch.h"

class ENEMY
{
private:
	double x, y;
	int gh[3];
	int width, height;
	int in_time, stop_time, out_time, shot_time;

	double angle;
	int hp;
	int item;

	int type;
	int stype;

	int m_pattern;
	int s_pattern;

	int count;
	bool deadflag;
	bool endflag;

	E_SHOT shot[ENEMY_SNUM ];
	bool sflag;
	int scount;

public:
	bool All();
	void Move();
	void Shot();
	void Draw();
	ENEMY( int type, int stype, int m_pattern, int s_pattern,
		int in_time, int stop_time, int shot_time, int out_time,
		int x, int y, int speed , int hp, int item );
};

