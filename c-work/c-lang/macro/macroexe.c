/*
 * macroexe.c
 * macro exercises.
 */
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main( int argc, char **argv ) {
  int a[ SIZE ];
  int i;
  int order = 1;
  for ( i = 0; i < SIZE; i++ ) {
    a[ i ] = rand() % 101;
  }
  printf( "input the order you wanna:" );
  scanf( " %d", &order );
  sort( a, SIZE );
# if order
  for ( i = 0; i < SIZE; i++ ) {
    printf( " %d ", a[ i ] );
  }
  printf( "\n" );
# else
  for ( i = SIZE - 1; i >= 0; i-- ) {
    printf( " %d ", a[ i ] );
  }
  printf( "\n" );
# endif
  return 0;
}
