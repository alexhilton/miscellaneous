/*
 * bitcount.c
 *
 * count all 1 bits in x.
 */
#include <stdio.h>

int bitcount( int x );

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
  int x, y;
  while ( fscanf( in, "%x", &x ) != EOF ) {
    y = bitcount( x );
    fprintf( out, "bitcount(0x%x) is %d\n", x, y );
  }

  fclose( in );
  fclose( out );

  return 0;
}

/* 
 * this program takes the advantages that x&x-1 will turns
 * off the last bit of x.
 */
int bitcount( int x ) {
  int i;
  for ( i = 0; x != 0; x &= (x-1), i++ )
    ;
  return i;
}
