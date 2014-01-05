/*
 * echoall.c
 * echo all command-line arguments and environment variables.
 */
#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int main( int argc, char **argv ) {
  int i;
  for ( i = 0; i < argc; i++ ) {
    printf( "argv[%d]: %s\n", i, argv[ i ] );
  }
  /*
  char **env;
  for ( env = environ; *env != NULL; env++ ) {
    printf( "%s\n", *env );
  }*/

  return 0;
}
