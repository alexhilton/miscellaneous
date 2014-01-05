/*
 * exercise 09 of chap 01, in <the c programming language> by K&R.
 * 
 * Replace string of blanks with a single space in input files.
 * this is another version using technique of IN & OUT KR
 */
#include <stdio.h>
#include <ctype.h>

const int IN = 1;
const int OUT = 0;

int main( int argc, char *argv[] ) {
  if ( argc < 2 ) {
    printf( "Missing input files.\n" );
    return 1;
  }
  FILE *in, *out;
  int i;
  int state;
  char ch;
  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[ i ], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    /* this is version is much more simple and stable */
    state = OUT;
    out = fopen( "output.dat", "w" );
    while ( (ch = fgetc( in )) != EOF ) {
      if ( !isspace( ch ) ) {
	state = OUT;
	fputc( ch, out );
      } else if ( state == OUT ) {
	state = IN;
	fputc( ch, out );
      }
    }
    fclose( in );
    fclose( out );
  }
  return 0;
}
