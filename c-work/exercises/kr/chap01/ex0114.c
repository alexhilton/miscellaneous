/*
 * exercise 0114
 *
 * print a histogram of the frequencies of different characters in its input.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "histogram.h"

#define MAX_SIZE 1000

int main( int argc, char *argv[ ] ) {
  if ( argc < 2 ) {
    fprintf( stderr, "Missing input files\n" );
    return 1;
  }
  int i, size;
  int a[ 3 ];
  FILE *in, *out;
  char ch;
  char *name[ ] = {
    "digit",
    "alpha",
    "other",
  };
  size = 3;
  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[ i ], "r" );
    out = fopen( "output.dat", "w" );
    if ( in == NULL || out == NULL ) {
      perror( argv[ i ] );
      return 1;
    }

    memset( a, 0, sizeof( a ) );
    while ( (ch = fgetc( in )) != EOF ) {
      if ( isdigit( ch ) ) {
	a[ 0 ]++;
      } else if ( isalpha( ch ) ) {
	a[ 1 ]++;
      } else {
	a[ 2 ]++;
      }
    }
    hshistogram( out, a, size, name );
    vshistogram( out, a, size, name );
    fclose( in );
    fclose( out );
  }
  return 0;
}
