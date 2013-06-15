#pragma once
#include "pch.h"
//#include "control.h"

class PLAYER{
private:
	double x, y;

	int width, height;
	int gh[3];

	float move;

	double xcount, ycount;

	int ix, iy, result;

	bool life;

	SHOT shot[PSHOT_NUM];

	int count;
private:
	void Move();
	void Draw();
	void Shot();

public:
	PLAYER();
	void GetPosition( double *x, double *y );
	void All();
};

