/*
 * mkstemp.c
 *
 * tmpnam() function is dangerous, better choice is mkstemp().
 * It is just like gets() and fgets().
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  char tf_path[ 64 ]; /* temp file path */
  int tfd = -1; /* UNIX file descriptor */
  FILE *in = NULL; 

  /*
   * '01-XXXXXX' this is the temporary file name template.
   * function mkstemp() will replace 'XXXXXX' with  proper
   * generated temporary filename.
   */
  strcpy( tf_path, "/tmp/01-XXXXXX" ); /* initial template */

  if ( (tfd = mkstemp( tf_path )) < 0 ) {
    /* an error occured */
    perror( tf_path );
    return 0;
  }

  printf( "using temp file: '%s'\n", tf_path );

  /**
   * fdopen() function open a file by its descriptor
   */
  in = fdopen( tfd, "w+" ); /* use FILE I/O */
  if ( in == NULL ) {
    perror( tf_path );
    return 0;
  }

  fprintf( in, "Written by PID=%ld\n", (long) getpid() );
  fclose( in );

  return 0;
}
