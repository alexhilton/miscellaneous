/*
 * exercise 0110 of <KR>
 * replace all tabs with \t, backstores with \b and backslash with \\.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
  int i;
  char ch;
  FILE *in;
  if ( argc < 2 ) {
    fprintf( stderr, "Error: Missing input file(s).\n" );
    exit( 1 );
  }
  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[ i ], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    while ( (ch = fgetc( in )) != EOF ) {
      if ( ch == '\t' ) {
	putchar( '\\' );
	putchar( 't' );
      } else if ( ch == '\b' ) {
	putchar( '\\' );
	putchar( 'b' );
      } else if ( ch == '\\' ) {
	putchar( '\\' );
	putchar( '\\' );
      } else {
	putchar( ch );
      }
    }
    fclose( in );
  }
  return 0;
}
