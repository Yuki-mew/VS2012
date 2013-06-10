#include "back.h"
#include "pch.h"

BACK::BACK(void)
{
	gh = LoadGraph("images/back.png");
	x = y = MARGIN;
}

void BACK::Draw(){
	DrawGraph( x, y, gh, FALSE );
	DrawGraph( x, y - 460, gh, FALSE );
	if(y==460+MARGIN){
		y=MARGIN;
	}
}

void BACK::Move(){
	y += BACK_SPEED;
}

void BACK::All(){
	Move();
	Draw();
}