/*
 * adventure some environment variable functions.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[], char *envp[] ) {
  char *str;
  str = getenv( "PATH" );
  printf( "PATH = %s\n", str );
  printf( "environment ABC=%s\n", getenv( "ABC" ) );
  putenv( "ABC=abcd" );
  printf( "environment ABC=%s\n", getenv( "ABC" ) );
  unsetenv( "ABC" );
  printf( "environment ABC=%s\n", getenv( "ABC" ) );
  /*int i;
  for ( i = 0; envp[ i ] != NULL; i++ ) {
    printf( "%s\n", envp[i] );
  }*/
  return 0;
}
