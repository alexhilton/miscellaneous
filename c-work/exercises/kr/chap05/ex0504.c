/**
 * ex0504.c
 * implement strend( s, t ), which returns 1 if the string t occurs at the end
 * of the string s, and zero otherwise.
 */
#include <stdio.h>

static int strend( char str[], char pattern[] );

int main( int argc, char **argv ) {
  char str1[ 128 ];
  char str2[ 128 ];
  printf( "input your prefix:" );
  scanf( "%s", str1 );
  printf( "input yoru suffix:" );
  scanf( "%s", str2 );
  if ( strend( str1, str2 ) ) {
    printf( "'%s' match '%s' at end\n", str2, str1 );
  } else {
    printf( "there are no resemblance between '%s' and '%s'\n", str1, str2 );
  }
  return 0;
}

static int strend( char *str, char *pattern ) {
  char *p = str, *q = pattern;
  while ( *p++ )
    ;
  p -= 2;
  while ( *q++ )
    ;
  q -= 2;
  while ( *q == *p ) {
    if ( q == pattern ) {
      return 1;
    }
    q--;
    p--;
  }
  return 0;
}
