/*
 * ex0303.c
 *
 * implement a function expand( s1, s2 ) which expands
 * regular expression like string such as "a-z" into
 * full list "abc...xyz". Make program robust enough to
 * handle special cases like "a-b-c", "--a-z".
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
    s2[ 0 ] = '\0';
  }

  fclose( in );
  fclose( out );

  return 0;
}

int expand( char s1[ ], char s2[ ] ) {
  int i, j;
  char ch;
  /* deal with leading white spaces and '-' */
  i = 0;
  while ( isspace( s1[ i ] ) ) {
    i++;
  }
  while ( s1[ i ] == '-' ) {
    i++;
  }

  /* deal with trailing white spaces and '-' */
  int len = strlen( s1 ) - 1;
  while ( isspace( s1[ len ] ) ) {
    len--;
  }
  while ( s1[ len ] == '-' ) {
    len--;
  }
  s1[ len+1 ] = '\0';

  j = 0;
  char start = s1[ i++ ];
  while ( s1[ i ] != '\0' ) {
    if ( s1[ i ] == '-' ) {
      i++;
      if ( isalnum( s1[ i ] ) ) {
	for ( ch = start; ch < s1[ i ]; ch++ ) {
	  s2[ j++ ] = ch;
	}
	start = s1[ i++ ];
      } else {
	return -1; /* error occured */
      }
    } else if ( isalnum( s1[ i ] ) ) {
      s2[ j++ ] = start;
      start = s1[ i++ ];
    } else {
      return -1;
    }
  }
  s2[ j++ ] = start;
  s2[ j ] = '\0';
  return 0;
}
