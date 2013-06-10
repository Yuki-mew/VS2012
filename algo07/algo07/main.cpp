#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int max;	//capacity of queue
	int num;	//size of queue
	int front;	//front cursor
	int rear;	//end cursor
	int *que;	//body of queue
} IntQueue;

//Initialize of Queue
int Initialize( IntQueue *q, int max ){
	q -> num = q -> front = q -> rear = 0;
	if( ( q -> que = calloc( max, sizeof( int ) ) ) == NULL ){
		q -> max = 0;
		return -1;
	}
	q -> max = max;
	return 0;
}

//Finalize of Queue
int Terminate( IntQueue *q ){
	if( q -> que != NULL ){
		free( q -> que );
		q -> max = q -> num = q -> front = q -> rear = 0;
	}
}

//Euque of the data fron Queue
int Enque( IntQueue *q, int x ){
	if( q -> num >= q -> max )
		return -1;
	else {
		q -> num++;
		q -> que[ q -> rear++ ] = x;
		if( q -> rear == q -> max ) q -> rear = 0;
		return 0;
	}
}

//Deque of the data from Queue 
int Deque( IntQueue *q, int *x ){
	if( q ->num <= 0 )
		return -1;
	else {
		q -> num--;
		*x = q -> que[ q -> front++ ];
		if( q -> front == q -> max )
			q -> front = 0;
		return 0;
	}
}

//Peek of the data from Queue 
int Peek( IntQueue *q, int *x ){
	if( q -> num <= 0 )
		return -1;
	*x = q -> que[ q -> front ];
	return 0;
}

//Capacity of Queue
int Capacity( const IntQueue *q ){
	return ( q -> max );
}

//Size of data in Queue
int Size( const IntQueue *q ){
	return ( q -> num );
}

//Display of all data in Queue
void Print( const IntQueue *q ){
	int i;
	for( i = 0; i < q -> num; i++ )
		printf( "%d ", q -> que[ i + q -> front % q -> max ] );
	putchar( '\n' );
}

int main( void ){
	IntQueue que;
	if( Initialize( &que, 10 ) == -1 ){
		puts( "�L���[�̐����Ɏ��s���܂����B" );
		return -1;
	}

	while( 1 ){
		int m, x;
		printf( "���݂̃f�[�^���F%d / %d\n", Size( &que ), Capacity( &que ) );
		printf( "(1)�G���L���[ (2)�f�L���[ (3)�s�[�N (4)�\�� (0)�I�� �F" );
		scanf( "%d", &m );
		if( m == 0 ) break;

		switch( m ){
		case 1:	//Enque
			printf("�f�[�^�F");
			scanf( "%d", &x );
			if( Enque( &que, x ) == -1 )
				puts( "\a�G���[�F�f�[�^�̃G���L���[�Ɏ��s���܂����B" );
			break;

		case 2:	//Deque
			if( Deque( &que, &x ) == -1 )
				puts( "\a�G���[�F�f�L���[�Ɏ��s���܂����B" );
			else
				printf( "�f�L���[�����f�[�^��%d�ł��B\n", x );
			break;

		case 3:	//Peek
			if( Peek( &que, &x ) == -1 )
				puts( "�s�[�N�Ɏ��s���܂����B" );
			else
				printf( "�s�[�N�����f�[�^��%d�ł��B\n, x" );
			break;
		case 4:
			Print( &que );
			break;
		}
	}
	Terminate( &que );
	return 0;
}