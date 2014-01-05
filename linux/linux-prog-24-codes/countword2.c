/*
 * word counter another version.
 * Here the word is defined as a strings of characters without 
 * white spaces.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int main( int argc, char *argv[] ) {
  int i, wcnt, state;
  char ch;
  FILE *in;

  if ( argc < 2 ) {
    fprintf( stderr, "Missing input file(s).\n" );
    exit( 1 );
  }

  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[ i ], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    wcnt = 0;
    /* 
     * this initialization is important
     * without it, you will get count less than real value.
     * But why initialize it as OUT, why not IN.
     * Because at the beginning of file, you are out of an string.
     */
    state = OUT; 
    while ( (ch = fgetc( in )) != EOF ) {
      if ( isspace( ch ) ) {
	state = OUT;
      } else if ( state == OUT ) {
	wcnt++;
	state = IN;
      }
    }
    printf( "%s: %d word(s).\n", argv[i], wcnt );
    fclose( in );
  }
  return 0;
}
