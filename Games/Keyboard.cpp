#include "Dxlib.h"

static int m_Key[256];

void Keyboard_Update()
{
	char tmpKey[256];
	GetHitKeyStateAll( tmpKey );
	for( int i=0; i<256; i++ )
	{
		if( tmpKey[i] != 0 )
		{
			m_Key[i]++;
		} else {
			m_Key[i] = 0;
		}
	}
}

int Keyboard_Get( int KeyCode )
{
	return m_Key[ KeyCode ];
}