/*
 * readpipe.c
 *
 * a program demonstrates how to read from a pipe.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main( int argc, char *argv[] ) {
  char buf[ 256 ];
  FILE *p = popen( "ps f", "r" ); /* popen open a pipe */

  if ( p == NULL ) {
    perror( "open pipe 'ps f'" );
    return 1;
  }

  /*
   * read the output of the pipe
   */
  while ( fgets( buf, sizeof( buf ), p ) != NULL ) {
    fputs( buf, stdout );
  }

  if ( pclose( p ) != 0 ) {
    perror( "pclose()" );
    return 1;
  }

  return 0;
}
