/*
 * ex0205.c
 *
 * write an implementation of any( char s1[ ], char s2[ ] ), which
 * returns the first location in the string s1 where any character
 * from the string s2 occurs.
 */
#include <stdio.h>

#define MAX_SIZE 128
int any( char s1[ ], char s2[ ] );

int main( int argc, char *argv[ ] ) {
  FILE *in, *out;

  in = fopen( "input.dat", "r" );
  if ( in == NULL ) {
    perror( "input.dat" );
    return 1;
  }
  out = fopen( "output.dat", "w" );
  if ( out == NULL ) {
    perror( "output.dat" );
    return 1;
  }
  char s1[ MAX_SIZE ];
  char s2[ MAX_SIZE ];
  int p;
  while ( fscanf( in, "%s %s", s1, s2 ) != EOF ) {
    p = any( s1, s2 );
    fprintf( out, "first location is: %d\n", p );
  }

  fclose( in );
  fclose( out );

  return 0;
}

int any( char s1[ ], char s2[ ] ) {
  int i, j;
  for ( i = 0; s1[ i ] != '\0'; i++ ) {
    for ( j = 0; s2[ j ] != '\0' && s2[ j ] != s1[ i ]; j++ )
      ;
    if ( s2[ j ] != '\0' ) {
      return i;
    }
  }
  return -1;
}
