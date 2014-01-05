/*
 * ex0208.c
 *
 * write a function to implement rigth rotation n-bits of an integer x
 * e.g. rrotate( 0x1234, 4 ) = 0x4123.
 */
#include <stdio.h>

int lrotate( int x, int n );
int rrotate( int x, int n );
int bitwidth( int x );

int main( int argc, char *argv[ ] ) {
  FILE *in, *out;

  in = fopen( "input.dat", "r" );
  if ( in == NULL ) {
    perror( "input.dat" );
    return 1;
  }
  out = fopen( "output.dat", "w" );
  if ( out == NULL ) {
    perror( "output.dat" );
    return 1;
  }
  int x, n, y;
  while ( fscanf( in, "%x %d", &x, &n ) != EOF ) {
    y = rrotate( x, n );
    fprintf( out, "rrotate(0x%x, %d) is 0x%x\n", x, n, y );
    y = lrotate( x, n );
    fprintf( out, "lrotate(0x%x, %d) is 0x%x\n", x, n, y );
  }

  fclose( in );
  fclose( out );

  return 0;
}

int rrotate( int x, int n ) {
  int y = ~(~0 << n);
  y &= x;
  x >>= n;
  int w = bitwidth( x );
  y <<= w;
  return y | x;
}

/* return the width of bits unsigned integer x */
int bitwidth( int x ) {
  int i = 0;
  while ( x > 0 ) {
    x >>= 1;
    i++;
  }
  return i;
}

int lrotate( int x, int n ) {
  int y = ~(~0 << n);
  int w = bitwidth( x );
  y <<= (w - n);
  y &= x;
  int k = ~y;
  y >>= (w - n);
  x &= k;
  x <<= n;
  printf( "y is 0x%x, x is 0x%x\n", y, x );
  return y | x;
}
