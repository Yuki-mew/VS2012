#include <stdio.h>
#include <String.h>
#include <limits.h>

char *bm_match( char *pat, char *txt ){
	char *pt = txt;
	char *pp = pat;

	while( *pt != '\0' && *pp != '\0' ){
		pp = pat;
		while( *pt == *pp ){
			if( pp == pat )	return ( pt );
			pt++;
			pp++;
		}
		pt++;
	}
	return (NULL);
}

/*
		// Boyer-Moore Method
char *bm_match( char *pat, char *txt ){
	char *pt;	// cursor of trace txt
	char *pp;	// cursor of trace pattern
	int txt_len = strlen( txt );	// string length of txt
	int pat_len = strlen( pat );	// string lenght of pattern
	int skip[ UCHAR_MAX + 1 ];	// skip table
	int i;

	for( i = 0; i <= UCHAR_MAX; i++ )	// make skip table
		skip[ i ] = pat_len;
	for( pp = pat; *pp != '\0'; pp++)
		skip[ *pp ] = strlen( pp ) - 1;
	skip[ *( pp - 1 ) ] = pat_len;	// movement of last pattern's character is string length of pattern 

	pt = txt + pat_len - 1;	// decide the character of comparing last pattern's character
	while( pt < txt + txt_len ){	// while compared charecter is beyond of text's last character
		pp = pat + pat_len - 1;	// last character of pattern
		while( *pt == *pp ){
			if( pp == pat )	return (pt);	// first pattern's character is match
			pp--;
			pt--;
		}
		pt += skip[ *pt ];
	}
	return ( NULL );
}
*/

	int main ( void ){

	char *s;
	char s1[ 80 ];	// text
	char s2[ 80 ];	// pattern

	printf("text:");
	scanf("%s", s1);

	printf("pattern:");
	scanf("%s", s2);

	s = bm_match(s2, s1);	// searching s2 from s1 using Boyer-Moore
	if( s == NULL )
		puts("No pattern in the text.");
	else
		printf("Found in the %d character.", s - s1 +1);

	return ( 0 );
}