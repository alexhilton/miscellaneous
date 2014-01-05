/*
 * This program demonstrates that how to change the pointer arguments
 * you cannot change it directly in a function, because argument in the 
 * funciton is just anohter copy of the real arguments, you can change the
 * area that pointer points to, but you cannot change pointer itself.
 * But how to change a pointer, such as allocating memory for it, through 
 * a function. Two way: one is pass the address of the pointers; another is
 * return the modified pointer as function return value, and assign it to 
 * real argument.
 */
#include <stdio.h>
#include <stdlib.h>

/* macros, constants, and types */
typedef struct Point {
	int x;
	int y;
} *Point;

/* function prototypes */
static int *fill( int *a, int size );
static Point getData( Point a );

int main( int argc, char **argv ) {
  int *a;
  int i, size = 10;
  /*
   * solution 2.
   */
  a = fill( a, size );
  for ( i = 0; i < size; i++ ) {
    printf( " %d ", a[ i ] );
  }
  printf( "\n" );
  free( a );
  Point c;
  /*
   * you cannot just use getData( c );
   * c = getData; solution 2.
   */
  c = getData( c );
  printf( " c is a point %d, %d\n", c->x, c->y );
  free( c );
  return 0;
}

static int *fill( int *a, int size ) {
  a = malloc( size * sizeof( int ) );
  int i;
  for ( i = 0; i < size; i++ ) {
    a[ i ] = i + 1;
  }
  /*
   * return it as value, to avoid error.
   */
  return a;
}

static Point getData( Point c ) {
  c = malloc( sizeof( *c ) );
  c->x = 10;
  c->y = 10;
  return c;
}
/* End of $Source$ */
