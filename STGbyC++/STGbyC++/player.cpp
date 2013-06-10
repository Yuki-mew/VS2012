#include "player.h"
#include "pch.h"


PLAYER::PLAYER()
{
	if(-1 == LoadDivGraph("images/player.png", 3, 3, 1, 29, 40, gh)){
		MSG("EROOR");
	}
	width = 29;
	height = 40;
	move = 1.0f;

	xcount = 0, ycount = 0;
	result = 0;
	ix = 0, iy = 0;

	x = 180, y = 400;

	life = true;

	memset( shot, 0, sizeof( shot ) );
	int temp = LoadGraph( "images/shot.png" );
	int w, h;
	GetGraphSize( temp, &w, &h );

	for( int i=0; i<PSHOT_NUM; ++i ){
		shot[i] .flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
	}
	count = 0;
}

void PLAYER::Move(){
	if(key[KEY_INPUT_LEFT]==1 || key[KEY_INPUT_RIGHT]==1){
		if(key[KEY_INPUT_UP]==1 || key[KEY_INPUT_DOWN]==1){
			move  = 0.71f;
		} else {
			move = 1.0f;
		}
	} else if(key[KEY_INPUT_UP]==1 || key[KEY_INPUT_DOWN]==1){
		move = 1.0f;
	}

	if(key[KEY_INPUT_LEFT]==1){
		if( MARGIN < x )
			x -= PLAYER_SPEED * move;
		else
			x = MARGIN;
	}
	if(key[KEY_INPUT_RIGHT]==1){
		if( x < MARGIN + WIDTH )
			x += (int)PLAYER_SPEED * move;
		else
			x = MARGIN + WIDTH;
	}

	if(key[KEY_INPUT_UP]==1){
		if( MARGIN < y )
			y -= (int)PLAYER_SPEED * move;
		else
			y = MARGIN;
	}
	if(key[KEY_INPUT_DOWN]==1){
		if( y < MARGIN + HEIGHT )
			y += (int)PLAYER_SPEED * move;
		else
			y = MARGIN + HEIGHT;
	}

	if(key[KEY_INPUT_LEFT]==1){
		result = 1;
	} else if(key[KEY_INPUT_RIGHT]==1){
		result = 2;
	} else {
		result = 0;
	}
}

void PLAYER::Draw(){

	for( int i=0; i<PSHOT_NUM; ++i ){
		if( shot[i].flag ){
			DrawGraph( shot[i].x - shot[i].width / 2, shot[i].y - shot[i].height / 2, shot[i].gh, TRUE );
		}
	}

	if(life){
		DrawGraph(x - width/2, y - height/2, gh[result], TRUE);
	}
}

void PLAYER::Shot()
{
	if( key[ KEY_INPUT_Z ] == 1 && count%6 == 0 ){
		for( int i = 0; i<PSHOT_NUM; ++i ){
			if( shot[i].flag == false ){
				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;
				break;
			}
		}
	}

	for( int i=0; i<PSHOT_NUM; ++i ){
		if( shot[i].flag ){
			shot[i].y -= PSHOT_SPEED;
			if( shot[i].y < -10 ){
				shot[i].flag = false;
			}
		}
	}
}

void PLAYER::All(){
	Move();
	Shot();
	Draw();

	++count;
}