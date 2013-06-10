#ifndef BATTLE_H

#define BATTLE_H

typedef struct
{
	int num;
	char name[10];
	int str;
	int def;
} Card;

int Enemy_SelectCard();
int BattleRandomDice( int );

void Battle_Initialize();
void Battle_Finalize();

void DamageNum_Draw( int, int );
void DamageNum(int, int );
void MaxDamageNum( int, int, int, int );

void Game_Start_SetCard();
//void Game_Start_Update();
void Game_Start_Draw();
void Battle_Start_OutCard();
void Selected_Card_Draw( int, int );
void BattleDiceEffect();
void DrawCard();

void DrawCard_Update();
void Battle_Calculate( int, int, int, int );
void Game_Result();

#endif