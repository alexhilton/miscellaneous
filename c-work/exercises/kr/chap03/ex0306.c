/*
 * ex0306.c
 *
 * write a version of itoa that accepts three arguments
 * n, s and w, where w is the minimum width and fill with
 * blanks if the width of n is less than w.
 */
#include <stdio.h>
#define abs( x ) ((x) < 0 ? -(x) : (x))

void reverse( char s[ ] );
void itoa( int n, char s[ ], int w );

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
  int n, w;
  char s[ 128 ];
  while ( fscanf( in, "%d %d", &n, &w ) != EOF ) {
    itoa( n, s, w );
    fprintf( out, "itoa(%d, %d) is '%s'\n", n, w, s );
  }

  fclose( in );
  fclose( out );

  return 0;
}

void reverse( char s[ ] ) {
  char *p, *q;
  p = q = s;
  while ( *q != '\0' ) {
    q++;
  }
  q--;
  while ( p < q ) {
    *p ^= *q ^= *p ^= *q;
    p++, q--;
  }
}

/*
 * itoa
 *
 * convert integer n into characters in s with specified width.
 * fill with blanks until width is full
 * and it can handle minimum negative number
 */
void itoa( int n, char s[ ], int w ) {
  int i, sign;
  sign = n;
  i = 0;
  do {
    s[ i++ ] = abs( n % 10 ) + '0';
  } while ( ( n /= 10 ) != 0 );
  if ( sign < 0 ) {
    s[ i++ ] = '-';
  }
  while ( i < w ) {
    s[ i++ ] = ' ';
  }
  s[ i ] = '\0';
  reverse( s );
}
