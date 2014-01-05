/*
 * ex0401.c
 *
 * implementation of strstr() of string.h library.
 */
#include <stdio.h>
#include <string.h>

#define SIZE 128
int getline( FILE *in, char s[ ], int lim );
int strrindex( char s[ ], char t[ ] );

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
  char s[ SIZE ], t[ SIZE ];
  int i;
  int n = 0;
  fscanf( in, "%d", &n );
  fgetc( in ); /* there are some weird things in I/O of C */
  while ( n-- ) {
    getline( in, s, SIZE );
    getline( in, t, SIZE );
    i = strrindex( s, t );
    fprintf( out, "strrindex(\n'%s', \n'%s')\n\t is %d\n\n", s, t, i );
  }

  fclose( in );
  fclose( out );

  return 0;
}

int getline( FILE *in, char s[ ], int lim ) {
  int i;
  char ch;
  i = 0;
  for ( ; i < lim && (ch = fgetc( in )) != EOF; i++ ) {
    if ( ch == '\n' ) {
      s[ i++ ] = '\0';
      return i;
    } else {
      s[ i ] = ch;
    }
  }
  s[ i ] = '\0';
  return i;
}

/*
int strrindex( char s[ ], char t[ ] ) {
  int i, j, k;
  int p = -1;
  for ( i = 0; s[ i ] != '\0'; i++ ) {
    for ( j = i, k = 0; t[ k ] != '\0' && s[ j ] == t[ k ]; j++, k++ )
      ;
    if ( k > 0 && t[ k ] == '\0' ) {
      p = i;
    }
  }
  return p;
}
*/

/* this is a more efficient strrindex */
int strrindex( char s[ ], char t[ ] ) {
  int i, j, k;
  for ( i = strlen( s ) - strlen( t ); i >= 0; i-- ) {
    for ( j = i, k = 0; t[ k ] != '\0' && s[ j ] == t[ k ]; j++, k++ )
      ;
    if ( k > 0 && t[ k ] == '\0' ) {
      return i;
    }
  }
  return -1;
}
