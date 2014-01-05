/*
 * implement copy file utility.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  FILE *in, *out;
  char ch;
  if ( argc != 3 ) {
    fprintf( stderr, "Missing input file\n" );
    return 0;
  }
  in = fopen( argv[1], "r" );
  if ( in == NULL ) {
    perror( argv[1] );
    return 0;
  }
  out = fopen( argv[2], "w" );
  if ( out == NULL ) {
    perror( argv[2] );
    return 0;
  }

  while ( (ch = fgetc( in )) != EOF ) {
    fputc( ch, out );
  }
  fclose( in );
  fclose( out );
  return 0;
}
