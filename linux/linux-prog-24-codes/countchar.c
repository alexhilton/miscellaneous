/*
 * count characters in a text file.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
  int i;
  char ch;
  int cnt;
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
    cnt = 0;
    while ( (ch = fgetc( in )) != EOF ) {
      cnt++;
    }
    printf( "%s: %d character(s).\n", argv[i], cnt );
    fclose( in );
  }
  return 0;
}
