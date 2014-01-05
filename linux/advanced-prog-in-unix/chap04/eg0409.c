/**
 * eg0409.c
 * Show you how to use function getcwd.
 * Again this function get current working directory for this process.
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "../com/comhdr.h"

static char *path_alloc( int *size );

int main( int argc, char **argv ) {
  char *p;
  int size;
  if ( chdir( ".." ) < 0 ) {
    fprintf( stderr, "chdir to '..' failed\n" );
  }
  p = path_alloc( &size );
  if ( getcwd( p, size ) == NULL ) {
    fprintf( stderr, "getcwd failed\n" );
  }
  printf( "cwd = %s\n", p );
  return 0;
}

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define PATH_MAX_GUESS 1024
#define SUSV3 200112L

static long posix_version   = 0;

static char *path_alloc( int *size ) {
  char *ptr;
  int s;

  if ( posix_version == 0 ) {
    posix_version = sysconf( _SC_VERSION );
  }
  printf( "posix_version = %ld\n", posix_version );

  if ( pathmax == 0 ) {
    errno = 0;
    if ( (pathmax = pathconf( "/", _PC_PATH_MAX )) < 0 ) {
      if ( errno == 0 ) {
	/* it is indeterminate we have to guess one */
	pathmax = PATH_MAX_GUESS;
      } else {
	err_sys( "pathconf error for _PC_PATH_MAX" );
      }
    } else {
      /* add one, since it is relative to root */
      pathmax++;
    }
  }

  /*
   * Standards prior to SUSv3 is unclear as to whether or not path included a
   * null byte at the end of path. We have to test it and add one more in case.
   */
  if ( posix_version < SUSV3 ) {
    s = pathmax + 1;
  } else {
    s = pathmax;
  }

  if ( (ptr = malloc( s )) == NULL ) {
    err_sys( "out of memory" );
  }
  if ( ptr != NULL ) {
    *size = s;
  }

  return ptr;
}
