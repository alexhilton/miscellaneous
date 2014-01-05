/*
 * exercise 0108.c
 * count tabs, blanks and newlines in a text file.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
  int tcnt, bcnt, ncnt, i;
  FILE *in;
  char ch;
  if ( argc == 1 ) {
    fprintf( stderr, "Missing input file(s).\n" );
    exit( 1 );
  }
  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[i], "r" );
    tcnt = bcnt = ncnt = 0;
    if ( in == NULL ) {
      perror( argv[i] );
      continue;
    }
    while ( (ch = fgetc( in )) != EOF ) {
      if ( ch == '\t' ) {
	tcnt++;
      } else if ( ch == ' ' ) {
	bcnt++;
      } else if ( ch == '\n' ) {
	ncnt++;
      }
    }
    printf( "%s: tabs: %d; blanks: %d; newlines: %d\n",
		    argv[i], tcnt, bcnt, ncnt );
  }
  return 0;
}
