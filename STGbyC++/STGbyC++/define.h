#pragma once

#include <windows.h>
#include <math.h>

#define PI 3.1415926f
#define PLAYER_SPEED 4

#define MSG(m){\
	MessageBox( NULL, m, "Message", MB_OK );}
extern char key[256];

#define MARGIN 10
#define BACK_SPEED 1;

struct SHOT{
	bool flag;
	double x;
	double y;
	int gh;
	int width, height;
};

struct E_SHOT{
	bool flag;
	double x;
	double y;
	double rad;
	int gh;
	int width, height;
	int pattern;
	double speed;
};

extern int g_count;

#define PSHOT_NUM 20
#define PSHOT_SPEED 14
#define ENEMY_SNUM 500

#define WIDTH 380
#define HEIGHT 460

struct ENEMYDATA {
	int type;
	int stype;
	int m_pattern;
	int s_pattern;
	int in_time;
	int stop_time;
	int shot_time;
	int out_time;
	int x;
	int y;
	int speed;
	int hp;
	int item;
};

#define ENEMY_NUM 10