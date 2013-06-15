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
	//�e����ŏ��ɕ`��
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

	//CONTROL�N���X�̎Q��
	CONTROL &control = CONTROL::GetInstance();
	double px,py;


	//���˃^�C�~���O�ɂȂ�����A�t���O�𗧂Ă�
	if(shot_time==g_count){
		sflag=true;
	}

	//�t���O�����Ă�Ƃ�����
	if(sflag){

		//�v���C���[�̈�擾
		control.GetPlayerPosition(&px,&py);

		//�G�ƃv���C���[�Ƃ̍��W�̍�����t���ڂ����߂�B
		//���񂾂����s
		if(scount==0)
			rad=atan2(py-y,px-x);


		switch(s_pattern){
			//�O���ɃV���b�g
		case 0:
			//5���[�v�Ɉ�񔭎ˁB20�܂łȂ̂�5�����ˁB
			if(scount%5==0 && scount<=20){
				for(int i=0;i<ENEMY_SNUM;++i){
					//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
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

			//�v���C���[�Ɍ������Ē����V���b�g
		case 1:
			//6���[�v�Ɉ�񔭎ˁB54�܂łȂ̂�10�����ˁB
			if(scount%6==0 && scount<=54){
				for(int i=0;i<ENEMY_SNUM;++i){
					//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
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

			//3�����V���b�g
		case 2:
			//10���[�v�Ɉ�񔭎ˁB1���[�v��3���Ȃ̂�5���[�v������ƂP�T������
			if(scount%10==0 && scount<=40){
				for(int i=0;i<ENEMY_SNUM;++i){
					//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
					if(shot[i].flag==false){
						shot[i].flag=true;
						shot[i].x=x;
						shot[i].y=y;

						//0�̎��͍����
						if(num==0){

							//�G�ƃv���C���[�Ƃ̋t���ڂ���10�x���������W�A������
							shot[i].rad=rad-(10*3.14/180);
							//1�̎��̓v���C���[�꒼��
						}else if(num==1){
							//�G�ƃv���C���[�Ƃ̋t���ڂ���
							shot[i].rad=rad;
							//2�̎��͉E���
						}else if(num==2){
							//�G�ƃv���C���[�Ƃ̋t���ڂ���10�x���������W�A������
							shot[i].rad=rad+(10*PI/180);

						}
						++num;

						//3�����˂�����,num��0�ɂ��ă��[�v�𔲂���B
						if(num==3){
							num=0;
							break;
						}
					}
				}
			}
			break;

			//���˃V���b�g
		case 3:
			//1���[�v����1������

			for(int i=0;i<ENEMY_SNUM;++i){
				//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
				if(shot[i].flag==false){
					shot[i].flag=true;
					shot[i].x=x;
					shot[i].y=y;
					//���񂾂�����������
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


	//�t���O�������Ă�e�̐�
	int s=0;

	//�t���O�����Ă�e�����A�e�̈ړ����s��
	for(int i=0;i<ENEMY_SNUM;++i){
		if(shot[i].flag){
			switch(shot[i].pattern){
				//�P���ɉ��ɔ���
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

			//�e����ʂ��͂ݏo����t���O��߂��B
			if(ShotOutCheck(i)){
				shot[i].flag=false;
				continue;
			}
			++s;
		}
	}
	//s���[���Ƃ������Ƃ͔��˒��̒e���Ȃ��B
	//����deadflag��TRUE�Ƃ������Ƃ͂��̓G�̃N���X�͏��ł����Ă��悢
	if(s==0 && deadflag){
		//�G�N���X���Ńt���O��TRUE�ɂ���
		endflag=true;
	}

	++scount;

}

bool ENEMY::ShotOutCheck(int i)
{
	//�e����ʂ��͂ݏo����t���O��߂��B
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