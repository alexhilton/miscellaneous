/*
 * check out sizeof( str ) and strlen( str ).
 */
#include <stdio.h>
#include <string.h>

int main() {
  char str[] = "hello";
  printf( "The string is '%s'\n", str );
  printf( "the length of it is 'strlen( %s )' = %d\n", str, strlen( str ) );
  printf( " while, 'sizeof( %s )' is %d\n", str, sizeof( str ) );
  return 0;
}
