#include "enemy.h"

ENEMY::ENEMY( int type,
			 int stype,
			 int m_pattern,
			 int s_pattern,
			 int in_time,
			 int stop_time,
			 int shot_time,
			 int out_time,
			 int x,
			 int y,
			 int speed,
			 int hp,
			 int item ){
	width = 27;
	height = 25;

	this -> type = type;
	this -> stype = stype;

	this -> m_pattern = m_pattern;
	this -> s_pattern = s_pattern;

	this -> x = x;
	this -> y = y;

	this -> in_time = in_time;
	this -> stop_time = stop_time;
	this -> shot_time = shot_time;
	this -> out_time = out_time;

	this -> hp = hp;
	this -> item = item;

	if( type == 0 ){
		LoadDivGraph( "images/enemy.png", 3, 1, 3, 27 ,25, gh );
	}

	int temp;
	if( stype == 0 ){
		temp = LoadGraph( "images/enemyshot1.png" );
	}

	int w, h;
	GetGraphSize( temp , &w, &h );

	for( int i=0; i<ENEMY_SNUM; ++i ){
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
		shot[i].pattern = s_pattern;
		shot[i].speed = speed;
		shot[i].x = x;
		shot[i].y = y;
	}

	count = 0;
	scount = 0;

	deadflag = false;
	endflag = false;
	sflag = false;
}

void ENEMY::Move(){
	if( in_time < g_count && g_count < stop_time ){
		y += 2;
	} else if( g_count > out_time ){
		y -= 2;
		if( y < -40 ){
			endflag = true;
		}
	}
}

void ENEMY::Draw(){
	int temp;

	for( int i=0; i<ENEMY_SNUM; ++i ){
		if( shot[i].flag ){
			DrawGraph( shot[i].x, shot[i].y, shot[i].gh, TRUE );
		}
	}

	if( !endflag ){
		temp = count % 40 / 10;
		if( temp == 3 )
			temp = 1;
		DrawGraph( x, y, gh[ temp ], TRUE );
	}
}

void ENEMY::Shot(){
	if( shot_time == g_count ){
		sflag = true;
	}

	if( sflag ){
		switch( s_pattern ){
		case 0:
			if( scount % 2 == 0 && scount <= 90 ){
				for( int i=0; i<ENEMY_SNUM; ++i ){
					if( shot[i].flag == false ){
						shot[i].flag = true;
						shot[i].angle = 0.0;
						shot[i].x = x;
						shot[i].y = y;
						break;
					}
				}
			}
			break;
		}

		int s=0;
		double angle = 0.0;
		for( int i=0; i<ENEMY_SNUM; ++i, angle += PI / 20 ){
			if( shot[i].flag ){
				shot[i].x += cos( angle ) * shot[i].speed;
				shot[i].y += sin( angle ) * shot[i].speed;
				if( shot[i].x < -20 || shot[i].x > 420 || shot[i].y < 20 || shot[i].y > 500 ){
					shot[i].flag = false;
					continue;
				}
				++s;
			}
		}
		if( s==0 && deadflag ){
			endflag = true;
		}

		++scount;
	}
}

bool ENEMY::All(){
	Move();
	Shot();
	Draw();
	++count;

	return endflag;
}