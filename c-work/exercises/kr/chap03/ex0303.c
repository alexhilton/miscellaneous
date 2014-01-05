/*
 * ex0303.c
 *
 * expand regular expression into its full list.
 * e.g. x-z = xyz
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 128

int expand( char s1[ ], char s2[ ] );

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
  char s1[ SIZE ], s2[ SIZE ];
  while ( fscanf( in, "%s", s1 ) != EOF ) {
    expand( s1, s2 );
    fprintf( out, "expansion of '%s' is '%s'\n", s1, s2 );
  }

  fclose( in );
  fclose( out );

  return 0;
}


int expand( char s1[ ], char s2[ ] ) {
  char ch;
  int i, j;
  i = 0;
  j = strlen( s1 ) - 1; /* because s[ strlen(s) ] is '\0' */
  while ( isspace( s1[ i ] ) ) {
    i++;
  }
  while ( isspace( s1[ j ] ) ) {
    j--;
  }
  while ( s1[ i ] == '-' ) {
    i++;
  }
  while ( s1[ j ] == '-' ) {
    j--;
  }
  s1[ j+1 ] = '\0';

  j = 0;
  while ( (ch = s1[ i++ ]) != '\0' ) {
    if ( s1[ i ] == '-' && s1[ i+1 ] >= ch ) {
      i++;
      while ( ch < s1[ i ] ) {
	s2[ j++ ] = ch++;
      }
    } else {
      s2[ j++ ] = ch;
    }
  }
  s2[ j ] = '\0';
  return 0;
}
