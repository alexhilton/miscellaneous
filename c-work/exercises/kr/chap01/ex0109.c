/*
 * exercise 0109.c
 * repalce a string of blanks with a single blank.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
  char ch; /* current character in the stream */
  char pch; /* previous character in the stream */
  FILE *in, *out; /* input and output file pointer */
  if ( argc < 2 ) {
    fprintf( stderr, "Missing input file.\n" );
    exit( 1 );
  }
  in = fopen( argv[ 1 ], "r" );
  if ( in == NULL ) {
    perror( argv[ 1 ] );
    exit( 1 );
  }
  if ( argc == 2 ) {
    out = stdout;
  } else {
    out = fopen( argv[ 2 ], "w" );
    if ( out == NULL ) {
      perror( argv[ 2 ] );
      exit( 1 );
    }
  }
  ch = pch = 'a'; /* initialize to avoid weard things */
  while ( (ch = fgetc( in )) != EOF ) {
    if ( ch != ' ' ) {
      fputc( ch, out );
      pch = ch;
    } else {
      if ( pch == ' ' ) {
	continue;
      } else {
	fputc( ' ', out );
      }
      pch = ' ';
    }
  }
  fclose( in );
  fclose( out );
  return 0;
}
