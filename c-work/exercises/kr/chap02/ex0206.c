/*
 * ex0206.c
 *
 * return x with the n-bit field that begin at position p set
 * to the rightmost n bits of y, leaving other bits unchanged.
 */
#include <stdio.h>

int setbits( unsigned x, int p, int n, unsigned y );

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
  int x, p, n, y, rc;
  while ( fscanf( in, "%x %d %d %x", &x, &p, &n, &y ) != EOF ) {
    rc = setbits( x, p, n, y );
    fprintf( out, "setbits(0x%x, %d, %d, 0x%x) = 0x%x\n", x, p, n, y, rc );
    printf( "0x1234 | 0x0000 = %x\n", x | 0 );
    printf( "0x1234 | 0x1111 = %x\n", x | ~0 );
  }

  fclose( in );
  fclose( out );

  return 0;
}

int setbits( unsigned x, int p, int n, unsigned y ) {
  int tmp = (x >> (p+1-n)) & ~(~0 << n);
  tmp |= (~0 << n);
  printf( "tmp is 0x%x\n", tmp );
  y |= (~(~0 << n));
  printf( "y is 0x%x\n", y );
  return tmp & y;
}
