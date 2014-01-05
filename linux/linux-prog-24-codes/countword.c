/*
 * countword.c
 * count the number of words in a text file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main( int argc, char *argv[] ) {
  int i, wcnt;
  FILE *in;
  char ch; /* current character */
  char pch; /* previous character */

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
    pch = ch = 'a';
    while ( (ch = fgetc( in )) != EOF ) {
      if ( isspace( ch ) ) {
	if ( !isspace( pch ) ) {
	  wcnt++;
	} else {
	  continue;
	}
	pch = ' ';
      } else {
	pch = ch;
      }
    }
    printf( "%s: %d word(s).\n", argv[ i ], wcnt );
    fclose( in );
  }
  return 0;
}
