/*
 * ex0304.c
 *
 * in a two's complement number representation, write a itoa
 * can handle the largest negative number.
 */
#include <stdio.h>

#define abs( x ) ((x) < 0 ? -(x) : (x))

void itoa( int n, char s[ ] );
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
  int n;
  char s[ 128 ];
  while ( fscanf( in, "%d", &n ) != EOF ) {
    itoa( n, s );
    fprintf( out, "%d, is '%s'\n", n, s );
  }

  fclose( in );
  fclose( out );

  return 0;
}


/*
 * function: itoa
 *
 * convert integer to its character string
 * assume that s is large enough to hold n
 */
void itoa( int n, char s[ ] ) {
  int i, sign;

  sign = n;
  i = 0;
  do {
    s[ i++ ] = abs( n % 10 ) + '0';
  } while ( ( n /= 10 ) != 0 );
  if ( sign < 0 ) {
    s[ i++ ] = '-';
  }
  s[ i ] = '\0';
  reverse( s );
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
