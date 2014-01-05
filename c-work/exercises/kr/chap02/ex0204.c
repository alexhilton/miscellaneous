/*
 * ex0204.c
 *
 * delete each characters in s1 that matches any character in the 
 * string s2.
 */
#include <stdio.h>

#define MAX_SIZE 128

int squeeze( char s1[ ], char s2[ ] );

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

  while ( fscanf( in, "%s %s", s1, s2 ) != EOF ) {
    fprintf( out, "s1='%s', s2='%s'\n", s1, s2 );
    if ( squeeze( s1, s2 ) != 0 ) {
      fprintf( out, "Error occured\n" );
      return 1;
    }
    fprintf( out, "after squeezing: '%s'\n", s1 );
  }

  fclose( in );
  fclose( out );

  return 0;
}

/*
 * Function: squeeze
 *
 * delete each char in s1 that matches any chars in s2.
 * this program is very smart, the usual way we do deletion from
 * an array is to move around. But the algo we used here is to record
 * 'survivors', that is use s1 to record the char that does not match
 * any char in s2.
 * and this is do deletion, thus k is always less or euqal than i,
 * so they won't overlap.
 */
int squeeze( char s1[ ], char s2[ ] ) {
  int i, j, k;
  for ( i = k = 0; s1[ i ] != '\0'; i++ ) {
    /* search s1[i] in string s2 */
    for ( j = 0; s2[ j ] != '\0' && s2[ j ] != s1[ i ]; j++ )
      ;
    /* if not found */
    if ( s2[ j ] == '\0' ) {
      /* record survivors */
      s1[ k++ ] = s1[ i ];
    }
  }
  s1[ k ] = '\0';
  return 0;
}
