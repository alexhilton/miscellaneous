/**
 * ex0505.c
 * implement strncpy, strncmp and strncat.
 */
#include <stdio.h>

static int strncpy( char *dst, char *src, int n );
static int strncmp( char *str1, char *str2, int n );
static int strncat( char *dst, char *src, int n );

int main( int argc, char *argv[] ) {
  char str1[ 128 ];
  char str2[ 128 ];
  int n;
  printf( "input a string:" );
  scanf( "%s", str1 );
  printf( "input another string:" );
  scanf( "%s", str2 );
  printf( "input the number of chars you wanna operate:" );
  scanf( "%d", &n );
  strncpy( str1, str2, n );
  printf( "strncpy, is: '%s'\n", str1 );

  printf( "input a string:" );
  scanf( "%s", str1 );
  printf( "input another string:" );
  scanf( "%s", str2 );
  printf( "input number you wanna operate:" );
  scanf( "%d", &n );
  printf( "strncmp, %d\n", strncmp( str1, str2, n ) );

  printf( "input a string:" );
  scanf( "%s", str1 );
  printf( "input another string:" );
  scanf( "%s", str2 );
  printf( "input number of chars you wanna operate:" );
  scanf( "%d", &n );
  strncat( str1, str2, n );
  printf( "strncat, '%s'\n", str1 );
  return 0;
}

static int strncpy( char *dst, char *src, int n ) {
  int i;
  for ( i = 0 ; (*dst = *src) != '\0' && i < n; i++, dst++, src++ )
    ;
  *dst = '\0';
  return 0;
}

static int strncmp( char *dst, char *src, int n ) {
  int i;
  for ( i = 0; *dst == *src && i < n; i++, dst++, src++ ) {
    if ( *dst == '\0' ) {
      return 0;
    }
  }
  return *dst - *src;
}

static int strncat( char *dst, char *src, int n ) {
  int i;
  while ( *dst ) {
    dst++;
  }
  for ( i = 0; i < n && (*dst = *src) != '\0'; i++, dst++, src++ )
    ;
  return 0;
}
