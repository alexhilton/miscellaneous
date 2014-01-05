/*
 * count the lines of an input file.
 */
#include <stdio.h>
#include <stdlib.h>

int count( FILE *in ) {
  char ch;
  int cnt = 0;
  while ( (ch = fgetc( in )) != EOF ) {
    if ( ch == '\n' ) {
      cnt++;
    }
  }
  return cnt;
}

int main( int argc, char *argv[] ) {
  FILE *in;
  if ( argc == 1 ) {
    fprintf( stderr, "Missing input file.\n" );
    return 0;
  }
  int i, cnt;
  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[i], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    cnt = count( in );
    printf( "%s: %d line(s).\n", argv[i], cnt );
    fclose( in );
  }
  return 0;
}
