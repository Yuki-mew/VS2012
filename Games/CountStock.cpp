#include "DxLib.h"
#include "CountStock.h"
#include "Game.h"

void CountCardStock_A( int CardA )
{
	switch( CardA )
	{
	case 0:
		if( attA == 0 )
		{
			CheckGameStart = 1;
		} else {
			attA = attA - 1;
			A_Card = -1;
		}
		break;
	case 1:
		if( defA == 0 ){
			CheckGameStart = 1;
		} else {
			defA = defA - 1;
			A_Card = -1;
		}
		break;
	case 2:
		if( techA == 0 )
		{
			CheckGameStart = 1;
		} else {
			techA = techA - 1;
			A_Card = -1;
		}
		break;
	}
}

int CheckCardStock_B( int CardB )
{
	switch( CardB )
	{
	case 0:
		if( attB == 0 ){
			return -1;
		} else {
			return 1;
		}
		break;
	case 1:
		if( defB == 0 ){
			return -1;
		} else {
			return 1;
		}
		break;
	case 2:
		if( techB == 0 ){
			return -1;
		} else {
			return 1;
		}
		break;
	default:
		return -1;
		break;
	}
}

void CountCardStock_B( int CardB )
{
	switch( CardB )
	{
	case 0:
			attB = attB - 1;
			B_Card = -1;
		break;
	case 1:

			defB = defB - 1;
			B_Card = -1;
		break;
	case 2:
			techB = techB - 1;
			B_Card = -1;
		break;
	}
}