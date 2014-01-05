/*
 * more.c
 *
 * a bare bone version of more command in Unix.
 */
#include <stdio.h>

int main( int argc, char *argv[ ] ) {
  if ( argc < 2 ) {
    printf( "Missing input files\n" );
    return 1;
  }
  int i;
  FILE *in;
  char ch;
  int line;

  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[ i ], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    line = 0;
    while ( (ch = fgetc( in )) != EOF ) {
      putchar( ch );
      if ( ch == '\n' ) {
        line++;
      }
      if ( line > 21 ) {
	printf( "\n Press Enter to continue..." );
	getchar();
	line = 0;
	putchar( '\n' );
      }
    }
    fclose( in );
  }
  return 0;
}
