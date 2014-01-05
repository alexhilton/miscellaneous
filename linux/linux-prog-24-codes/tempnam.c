/*
 * tempnam.c
 *
 * trick about tempnam() function to create temporary file.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  char *tf_path = NULL;
  FILE *tin = NULL;

  /**
   * Prototype of tempnam().
   * char *tempnam( const char *dir, const char *prefix ).
   * returned value is filename of created temporary file
   * first argument 'dir' specify directory path where temporary
   * will be created.
   * 'prefix' is the prefix of temporary file name.
   * tempnam() will do following things when creating a tmp file:
   * 	1 first check whether environment variable TMPDIR is set
   * 	   if set, use it as dir, if not go to 2
   * 	2 then check agument dir, if it is set use it, else go to
   * 	   three.
   * 	3 check macro L_tmdir in <stdio.h>, if not goto 4
   * 	4 use /tmp as tmporary dir.
   */
  if ( (tf_path = tempnam( "./my_tmp", "tmp-" )) == NULL ) {
    perror( tf_path );
    return 0;
  }

  printf( "temp. file name is '%s'\n", tf_path );

  /* 'w+' means write+read */
  if ( (tin = fopen( tf_path, "w+" )) == NULL ) {
    perror( tf_path );
    return 0;
  }

  fprintf( tin, "PID %ld was here.\n", (long) getpid() );
  fclose( tin );

  free( tf_path );

  return 0;
}
