/*
 * ex0413.c
 * a recursive version of reverse a string.
 */
#include <stdio.h>
#include <string.h>

void reverse( char str[], int left, int right );
void do_reverse( char str[] );

int main( int argc, char **argv ) {
  char str[ 128 ];
  printf( "input a string...\n" );
  fgets( str, sizeof( str ), stdin );
  str[ strlen( str ) - 1 ] = '\0';
  do_reverse( str );
  printf( "the reverse of your input string is:\n%s\n", str );
  return 0;
}

void do_reverse( char str[] ) {
  reverse( str, 0, strlen( str ) - 1 );
}

void reverse( char str[], int left, int right ) {
  if ( left < right ) {
    char ch = str[ left ];
    str[ left ] = str[ right ];
    str[ right ] = ch;
    reverse( str, ++left, --right );
  }
}
