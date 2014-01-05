/*
 * exercise 0119
 *
 * reverse a line and display it on console.
 */
#include <stdio.h>

#define swap( a, b ) { a ^= b ^= a ^= b; }
#define MAX_SIZE 1000

int reverse( char s[ ] );
int getline( FILE *in, char s[ ], int lim );

int main( int argc, char *argv[ ] ) {
  if ( argc != 2 ) {
    printf( "Missing input files.\n" );
    return 1;
  }
  char a[ MAX_SIZE ];
  int lim = MAX_SIZE;
  FILE *in;
  if ( (in = fopen( argv[ 1 ], "r" )) == NULL ) {
    perror( argv[ 1 ] );
    return 1;
  }
  int len;
  lim = MAX_SIZE;
  while ( (len = getline( in, a, lim )) >= 0 ) {
    if ( len == 0 ) {
      continue;
    }
    if ( reverse( a ) != 0 ) {
      printf( "Error occured\n" );
      continue;
    } else {
      printf( "%s\n", a );
    }
  }
  fclose( in );
  return 0;
}

int reverse( char s[ ] ) {
  char *p, *q;
  q = p = s;
  while ( *q++ )
    ;
  q--;
  q--;
  while ( p < q ) {
    swap( *p, *q );
    p++, q--;
  }
  return 0;
}

int getline( FILE *in, char s[ ], int lim ) {
  char ch;
  int i = 0;
  for ( ; i < lim && (ch = fgetc(in)) != EOF && ch != '\n'; i++ ) {
    s[ i ] = ch;
  }
  /* see that, i is the length, and s[i] is '\0' */
  s[ i ] = '\0';
  /* return code depends on what the ch is */
  if ( ch == EOF || i > lim ) {
    return -1; /* end-of-file */
  }
  return i;
}
