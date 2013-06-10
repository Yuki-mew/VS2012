#include <stdio.h>
#define MAX 10

typedef struct {
	int max; //capacity of stack
	int ptr; //stack pointer
	int stk[ MAX ]; // stack
} IntStack;

// Initialize the Stack
int Initialize( IntStack *s, int max ){
	s -> ptr = max-1;
	s -> max = max;
	return ( 0 );
}

//push the data from the stack
int Push( IntStack *s, int x ){
	if( s -> ptr <= 0 ) return -1; //stack filled
	s -> stk[ s -> ptr-- ] = x;
	return ( 0 );
}

//pop the data to from the stack
int Pop( IntStack *s, int *x ){
	if( s -> ptr >= s -> max ) return -1;
	*x = s -> stk[ ++s -> ptr ];
	return ( 0 );
}

//peek the data from the stack
int Peek( IntStack *s, int *x ){
	if( s -> ptr >= s -> max ) return -1;
	*x = s -> stk[ s -> ptr + 1 ];
	return ( 0 );
}

//Capacity of Stack
int Capacity( const IntStack *s ){
	return ( s -> max );
}

//the number of data in the sack
int Size( const IntStack *s ){
	return ( s -> max - s -> ptr );
}

//display of all data in the stack
void Print( const IntStack *s ){
	int i;
	for( i = s -> max - 1; i > s-> ptr; i-- )
		printf("%d ", s -> stk[i]);
	putchar( '\n' );
}

int main ( void ){
	IntStack s;
	Initialize( &s, MAX );
	while( 1 ){
		int menu, x;
		printf( "現在のデータ数：%d / %d\n", Size( &s ), Capacity( &s ) );
		printf(" ptr= %d\n ", s.ptr);
		printf( "(1) プッシュ, (2)ポップ, (3)ピーク, (4)表示, (0)終了：" );
		scanf( "%d", &menu );
		if( menu == 0 ) break;

		switch( menu ){
		case 1: //Push
			printf("データ：");
			scanf( "%d", &x );
			if( Push( &s, x ) == -1 )
				puts( "\aエラー：プッシュに失敗しました。" );
			break;
		case 2: //Pop
			if( Pop( &s, &x ) == -1 )
				puts( "\aエラー：ポップに失敗しました。" );
			else
				printf( "ポップしたデータは%dです。\n", x );
			break;
		case 3: //Peek
			if( Peek( &s, &x ) == -1 )
				puts( "\aエラー：ピークに失敗しました。" );
			else
				printf( "ピークしたデータは%dです。\n", x );
			break;
		case 4:
			Print( &s );
			break;
		}
	}
	return ( 0 );
}