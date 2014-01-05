/*
 * getbits.c
 *
 * return n-bit field of x.
 */
#include <stdio.h>

int getbits( unsigned x, int p, int n );

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
  int x, p, n;
  int y;
  while ( fscanf( in, "%x %d %d", &x, &p, &n ) != EOF ) {
    y = getbits( x, p, n );
    fprintf( out, "%d-bit field of 0x%x at %d is %d\n", n, x, p, y );
  }

  fclose( in );
  fclose( out );

  return 0;
}

int getbits( unsigned x, int p, int n ) {
  return ( x >> (p+1-n) ) & ~( ~0 << n );
}
