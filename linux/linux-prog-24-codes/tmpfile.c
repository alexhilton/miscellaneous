/*
 * tmpfile.c
 *
 * another fucntion used to create temporary file.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  FILE *tin = NULL; 
  char buf[ 128 ];

  if ( (tin = tmpfile()) == NULL ) {
    perror( "tmpfile()" );
    return 0;
  }

  fprintf( tin, "PID %ld was here.\n", (long) getpid() );
  fflush( tin );

  rewind( tin );
  fgets( buf, sizeof( buf ), tin );
  /* the annoying newline got by fgets() */
  printf( "GOT: %s", buf );

  fclose( tin );

  return 0;
}
