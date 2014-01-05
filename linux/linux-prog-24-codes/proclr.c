/*
 * proclr.c
 *
 * process clear function.
 * clear temporary files.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

static char *tf_path = NULL;

static void clearup() {
  printf( "clearup() called\n" );
  if ( tf_path != NULL ) {
    printf( "Cleaning up temporary file '%s'\n", tf_path );
    unlink( tf_path );
    free( tf_path );
  }
}

int main( int argc, char *argv[] ) {
  FILE *tin = NULL; /* initialization is important */

  if ( atexit( clearup ) != 0 ) {
    /* error occured */
    perror( "atexit( clearup )" );
    return 0;
  }

  if ( (tf_path = tempnam( "./my_tmp", "tmp-" )) == NULL ) {
    perror( tf_path );
    return 0;
  }

  printf( "Temp. file name is %s\n", tf_path );

  if ( (tin = fopen( tf_path, "w+" )) == NULL ) {
    perror( tf_path );
    return 0;
  }

  fprintf( tin, "PID %ld was here.\n", (long) getpid() );
  fclose( tin );

  return 0;
}
