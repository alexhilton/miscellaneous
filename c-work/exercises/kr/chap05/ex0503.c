/*
 * ex0503.c
 * implement strcat() in the standard library.
 */
#include <stdio.h>

static int strcat( char dst[], char src[] );

int main( int argc, char *argv[] ) {
  char str1[ 128 ];
  char str2[ 128 ];
  printf( "please input prefix:" );
  scanf( "%s", str1 );
  printf( "please input suffix:" );
  scanf( "%s", str2 );
  if ( strcat( str1, str2 ) != 0 ) { 
    /* something is wrong */
    printf( "something is wrong!\n" );
  } else {
    printf( "your lucky string: '%s'\n", str1 );
  }
  return 0;
}

static int strcat( char *dst, char *src ) {
  while ( *dst ) {
    dst++;
  }
  while ( *dst = *src ) {
    dst++;
    src++;
  }
  return 0;
}
