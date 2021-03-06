#ifndef GAME_H

#define GAME_H

#define PI 3.141592654

extern int CheckGameStart;
extern int Parallel;
extern int CheckCardFlash;
extern int A_HP;
extern int B_HP;
extern int A_Card;
extern int B_Card;
extern int ACardTemp;
extern int BCardTemp;
extern int DiceTempA;
extern int DiceTempB;

extern int attA, defA, techA;
extern int attB, defB, techB;

void Game_Initialize();	//初期化
void Game_Finalize();	//終了処理
void Game_Update();
void Game_Draw();

#endif