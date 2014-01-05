/*
 * strindex.c
 *
 * implementation of strstr() of string.h library.
 */
#include <stdio.h>

#define SIZE 128
int getline( FILE *in, char s[ ], int lim );
int strindex( char s[ ], char t[ ] );

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
  fgetc( in );
  while ( n-- ) {
    getline( in, s, SIZE );
    getline( in, t, SIZE );
    i = strindex( s, t );
    fprintf( out, "strindex(\n'%s', \n'%s')\n\t is %d\n\n", s, t, i );
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

int strindex( char s[ ], char t[ ] ) {
  int i, j, k;
  for ( i = 0; s[ i ] != '\0'; i++ ) {
    for ( j = i, k = 0; t[ k ] != '\0' && s[ j ] == t[ k ]; j++, k++ )
      ;
    if ( k > 0 && t[ k ] == '\0' ) {
      return i;
    }
  }
  return -1; /* no match */
}
