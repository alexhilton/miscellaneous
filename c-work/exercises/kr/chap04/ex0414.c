/*
 * ex0414.c
 * swap to variables for specified type t in the form of macro:
 * swap( t, x, y )
 */
#include <stdio.h>

#define swap( t, x, y ) { \
  t tmp; \
  tmp = x; \
  x = y; \
  y = tmp; \
  }

int main( int argc, char **argv ) {
  typedef int t;
  int a = 10;
  int b = 22;
  printf( "a = %d, b = %d before swapping\n", a, b );
  swap( int, a, b );
  printf( "after swapping a = %d, b = %d\n", a, b );
  double c = 12.0;
  double d = 24.0;
  printf( "c = %.2lf, d = %.2lf before swapping\n", c, d );
  swap( double, c, d );
  printf( "after swapping, c = %.2lf, d = %.2lf\n", c, d );
  return 0;
}
