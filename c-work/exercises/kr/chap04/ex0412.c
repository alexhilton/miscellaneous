/*
 * ex0412.c
 * a recursive version of itoa( n ).
 */
#include <stdio.h>
#include <string.h>

#define swap( a, b ) { \
  a -= b; \
  b += a; \
  a = b - a; \
}

void reverse( char str[] );

void itoa( int n, char str[], int i );

int main( int argc, char **argv ) {
  char str[ 128 ];
  int n;
  printf( "input a integer, we will covert it to string for you:\n" );
  scanf( "%d", &n );
  printf( "converting %d to a string, please wait...\n", n );
  itoa( n, str, 0 );
  reverse( str );
  printf( "the string format is: '%s'\n", str );
  return 0;
}

void itoa( int n, char str[], int i ) {
  if ( n < 0 ) {
    str[ i++ ] = '-';
    n = -n;
  }
  if ( n == 0 ) {
    str[ i ] = '\0';
  } else {
    str[ i++ ] = n % 10 + '0';
    itoa( n / 10, str, i );
  }
}

void reverse( char str[] ) {
  int i = 0, len;
  if ( str[ 0 ] == '-' ) {
    i = 1;
  }
  for ( len = strlen( str ) - 1; i < len; i++, len-- ) {
    swap( str[ i ], str[ len ] );
  }
}
