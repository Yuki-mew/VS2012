#include "control.h"
#include "pch.h"
char key[256];
int g_count = 0;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){

	ChangeWindowMode(TRUE);

	if(DxLib_Init() == -1){
		return -1;
	}
	
	CONTROL *control = new CONTROL;

	while(ScreenFlip() == 0
		&& ProcessMessage() ==0
		&& ClearDrawScreen()==0
		&& GetHitKeyStateAll(key)==0 ){
			control -> All();
			DrawFormatString( 200, 200, GetColor( 0, 0, 0 ), "g_count == [ %d ]", g_count );
	}

	DxLib_End();

	return 0; 
}