#include "pch.h"

class PLAYER{
private:
	double x, y;
	double xcount, ycount;
	int width, height;
	int gh[3];
	float move;
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
	void All();
};

