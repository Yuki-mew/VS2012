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
				 switch(stype){
				 case 0:
					 temp=LoadGraph("enemyshot1.png");
					 break;
				 case 1:
					 temp=LoadGraph("enemyshot2.png");
					 break;
				 case 2:
					 temp=LoadGraph("enemyshot3.png");
					 break;

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
				 num = 0;
				 rad = 0;

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

void ENEMY::Draw()
{
	int temp;
	//弾から最初に描画
	for(int i=0;i<ENEMY_SNUM;++i){
		if(shot[i].flag){
			if(stype==0 || stype==2){
				DrawGraph(shot[i].x-shot[i].width/2,shot[i].y-shot[i].height/2,shot[i].gh,true);
			}else{
				DrawRotaGraph(shot[i].x,shot[i].y,1.0,shot[i].rad+(90*PI/180),shot[i].gh,true);
			}
		}
	}
	if(!deadflag){

		temp= count%40/10;
		if(temp==3)
			temp=1;
		DrawGraph(x-width/2,y-height/2,gh[temp],TRUE);
	}
}


void ENEMY::Shot()
{

	//CONTROLクラスの参照
	CONTROL &control = CONTROL::GetInstance();
	double px,py;


	//発射タイミングになったら、フラグを立てる
	if(shot_time==g_count){
		sflag=true;
	}

	//フラグ立ってるときだけ
	if(sflag){

		//プレイヤーの一取得
		control.GetPlayerPosition(&px,&py);

		//敵とプレイヤーとの座標の差から逆正接を求める。
		//初回だけ実行
		if(scount==0)
			rad=atan2(py-y,px-x);


		switch(s_pattern){
			//前方にショット
		case 0:
			//5ループに一回発射。20までなので5発発射。
			if(scount%5==0 && scount<=20){
				for(int i=0;i<ENEMY_SNUM;++i){
					//フラグが立ってない弾を探して、座標等をセット
					if(shot[i].flag==false){
						shot[i].flag=true;
						shot[i].x=x;
						shot[i].y=y;
						shot[i].rad=rad;
						break;
					}
				}

			}
			break;

			//プレイヤーに向かって直線ショット
		case 1:
			//6ループに一回発射。54までなので10発発射。
			if(scount%6==0 && scount<=54){
				for(int i=0;i<ENEMY_SNUM;++i){
					//フラグが立ってない弾を探して、座標等をセット
					if(shot[i].flag==false){
						shot[i].flag=true;
						shot[i].x=x;
						shot[i].y=y;
						shot[i].rad=rad;
						break;
					}
				}

			}
			break;

			//3直線ショット
		case 2:
			//10ループに一回発射。1ループに3発なので5ループさせると１５発発射
			if(scount%10==0 && scount<=40){
				for(int i=0;i<ENEMY_SNUM;++i){
					//フラグが立ってない弾を探して、座標等をセット
					if(shot[i].flag==false){
						shot[i].flag=true;
						shot[i].x=x;
						shot[i].y=y;

						//0の時は左より
						if(num==0){

							//敵とプレイヤーとの逆正接から10度引いたラジアンを代入
							shot[i].rad=rad-(10*3.14/180);
							//1の時はプレイヤー一直線
						}else if(num==1){
							//敵とプレイヤーとの逆正接を代入
							shot[i].rad=rad;
							//2の時は右より
						}else if(num==2){
							//敵とプレイヤーとの逆正接から10度足したラジアンを代入
							shot[i].rad=rad+(10*PI/180);

						}
						++num;

						//3発発射したら,numを0にしてループを抜ける。
						if(num==3){
							num=0;
							break;
						}
					}
				}
			}
			break;

			//乱射ショット
		case 3:
			//1ループ毎に1発発射

			for(int i=0;i<ENEMY_SNUM;++i){
				//フラグが立ってない弾を探して、座標等をセット
				if(shot[i].flag==false){
					shot[i].flag=true;
					shot[i].x=x;
					shot[i].y=y;
					//初回だけ乱数初期化
					if(num==0)
						srand((unsigned int)time(NULL));

					shot[i].rad=atan2(py-y,px-x)-(60*PI/180)+((rand()%120)*PI/180);
					++num;
					break;
				}
			}
			break;
		}
	}


	//フラグが立ってる弾の数
	int s=0;

	//フラグ立ってる弾だけ、弾の移動を行う
	for(int i=0;i<ENEMY_SNUM;++i){
		if(shot[i].flag){
			switch(shot[i].pattern){
				//単純に下に発射
			case 0:
				shot[i].y+=shot[i].speed;
				break;

			case 1:
				shot[i].x+=shot[i].speed*cos(shot[i].rad);
				shot[i].y+=shot[i].speed*sin(shot[i].rad);
				break;
			case 2:
				shot[i].x+=shot[i].speed*cos(shot[i].rad);
				shot[i].y+=shot[i].speed*sin(shot[i].rad);
				break;
			case 3:
				shot[i].x+=shot[i].speed*cos(shot[i].rad);
				shot[i].y+=shot[i].speed*sin(shot[i].rad);
				break;

			}

			//弾が画面をはみ出たらフラグを戻す。
			if(ShotOutCheck(i)){
				shot[i].flag=false;
				continue;
			}
			++s;
		}
	}
	//sがゼロということは発射中の弾がない。
	//かつdeadflagがTRUEということはこの敵のクラスは消滅させてもよい
	if(s==0 && deadflag){
		//敵クラス消滅フラグをTRUEにする
		endflag=true;
	}

	++scount;

}

bool ENEMY::ShotOutCheck(int i)
{
	//弾が画面をはみ出たらフラグを戻す。
	if(shot[i].x<-20 || shot[i].x>420 || shot[i].y<-20 || shot[i].y>500){
		return true;
	}else{
		return false;
	}
}



bool ENEMY::All(){
	Move();
	Shot();
	Draw();
	++count;

	return endflag;
}