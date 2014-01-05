/*
 * strexe.c
 * string exercises.
 */
#include <stdio.h>

void printDigit( int n );

int main( void ) {
  int value;
  for ( value  = 1; value < 101; value++ ) {
    printf( "%s\n", ( "************" + ( value % 10 - 2 ) ) );
  }
  printDigit( 1998 );
  printf( "\n" );
  return 0;
}

void printDigit( int n ) {
  if ( n < 10 ) {
    putchar( "0123456789"[ n ] );
  } else {
    putchar( "0123456789"[ n % 10 ] );
    printDigit( n / 10 );
  }
}
