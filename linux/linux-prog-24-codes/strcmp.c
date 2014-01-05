/*
 * implement strcmp function.
 */
#include <stdio.h>
#include <string.h>

int scmp( char *str1, char *str2 );

int main() {
  char str1[ 20 ], str2[ 20 ];
  printf( "input two strings, the comparision result will displayed:\n" );
  printf( "?: " );
  scanf( "%s", str1 );
  printf( "?: " );
  scanf( "%s", str2 );
  printf( "the comparision result is %d\n", scmp( str1, str2 ) );
  printf( "while the standard strcmp is %d\n", 
		  strcmp( str1, str2 ) );
  return 0;
}

int scmp( char *str1, char *str2 ) {
  while ( *str1 == *str2 ) {
    if ( *str1 == '\0' ) {
      return 0;
    }
    str1++, str2++;
  }
  return *str1 - *str2;
}
