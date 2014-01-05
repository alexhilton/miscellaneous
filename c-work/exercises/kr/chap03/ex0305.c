/*
 * ex0305.c
 *
 * write a function itob( n, s, b ) that converts the integer n
 * into a base b character representation in the string s.
 */
#include <stdio.h>
#define abs( x ) ((x) < 0 ? -(x) : (x))

void itob( int n, char s[ ], int b );
void reverse( char s[ ] );

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
  int n, b;
  char s[ 128 ];
  while ( fscanf( in, "%d %d", &n, &b ) != EOF ) {
    itob( n, s, b );
    fprintf( out, "%d to base %d is '%s'\n", n, b, s );
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

/* least negative number is able to handle */
void itob( int n, char s[ ], int b ) {
  int i, j, sign;
  sign = n;
  i = 0;
  do {
    j = abs( n % b );
    s[ i++ ] = ( j <= 9 ) ? ( j + '0' ) : ( j + 'a' - 10 );
  } while ( ( n /= b ) != 0 );
  if ( sign < 0 ) {
    s[ i++ ] = '-';
  }
  s[ i ] = '\0';
  reverse( s );
}
