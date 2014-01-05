/*
 * tmpnam.c
 *
 * a program to demonstrate how to use tmpnam() function,
 * and what it can do.
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  char *tmp_pathname; /* temporary file full name */
  FILE *in = NULL; /* opened temp file */

  if ( (tmp_pathname = tmpnam( NULL )) == NULL ) {
    fprintf( stderr, "%s: generating a temp file name\n", strerror( errno ) );
    return 0;
  }

  printf( "Using temp file: %s\n", tmp_pathname );

  if ( (in = fopen( tmp_pathname, "r" )) == NULL ) {
    perror( tmp_pathname );
    return 0;
  }

  fclose( in );
  return 0;
}
