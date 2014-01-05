/**
 * how to swap two variables effectively
 */
#include <stdio.h>

/* version one: bitwise */
/**
 * use bitwise operators to swap two integers
 * note: integers only
 */
void swapbitwise( int *a, int *b ) {
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

/* version two: minus */
/**
 * use minus
 * note: integers
 */
void swapminusint( int *a, int *b ) {
  *a -= *b;
  *b += *a;
  *a = (*b - *a);
}

/* version two: minus */
/**
 * use minus
 * note: floating point
 */
void swapminusfloat( double *a, double *b ) {
  *a -= *b;
  *b += *a;
  *a = (*b - *a);
}

int main( int argc, char **argv ) {
  int a, b;
  double c, d;
  printf( "integers:\n" );
  scanf( "%d %d", &a, &b );
  printf( "version one\n" );
  swapbitwise( &a, &b );
  printf( "a = %d, b = %d\n", a, b );
  printf( "version two\n" );
  swapminusint( &a, &b );
  printf( "a = %d, b = %d\n", a, b );

  printf( "floating point\n" );
  scanf( "%lf %lf", &c, &d );
  swapminusfloat( &c, &d );
  printf( "c = %lf, d = %lf\n", c, d );
  return 0;
}
