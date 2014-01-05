/*
 * cmdline.c
 * a program about command line argument.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
  printf( "I wanna know the argv[ 0 ], it is: %s\n", argv[ 0 ] );
  if ( argc < 2 ) {
    printf( "No inputs\n" );
  } else {
    int sum = 0, i;
    for ( i = 1; i <= argc; i++ ) {
      sum += atoi( argv[ i ] );
    }
    printf( "the sum is: %d\n", sum );
  }
  return 0;
}
