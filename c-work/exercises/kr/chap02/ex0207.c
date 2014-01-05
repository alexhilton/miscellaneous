/*
 * ex0207.c
 *
 * write a function invert( x, p, n ) taht returns x with the n bits
 * that begin at position p inverted ( or complement ), leaving other
 * btis unchanged
 */
#include <stdio.h>

int invert( int x, int p, int n );

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
  int x, p, n, y;
  while ( fscanf( in, "%x %d %d", &x, &p, &n ) != EOF ) {
    y = invert( x, p, n );
    fprintf( out, "invert(0x%x, %d, %d) = 0x%x\n", x, p, n, y );
  }

  fclose( in );
  fclose( out );

  return 0;
}

int invert( int x, int p, int n ) {
  int y;
  y = (~(~0 << n)) << ( p + 1 - n);
  return y ^ x;
}
