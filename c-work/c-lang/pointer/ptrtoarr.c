/*
 * ptrtoarr.c
 * this program demonstrates the pointer to array.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  int ( *a )[ 10 ]; /* a is a pointer to a 10-size-int-array*/
  a = ( int ( * )[ 10 ] ) malloc( 10 * sizeof( int ) );
  int i;
  for ( i = 0; i < 10; i++ ) {
    ( *a )[ i ] = i;
    printf( " %d ", ( *a )[ i ] );
  }
  printf( "\n" );
  printf( "sizeof( *a ) is %d\n", sizeof( *a ) );
  printf( "sizeof( a ) is %d\n", sizeof( a ) );

  return 0;
}
