/**
 * eg0202.c
 * Dynamically allocate space for pathname.
 * Through this example you can get a cue that how to write portable codes.
 * If the macro PATH_MAX has been defined, then we are set. If not, we use
 * pathconf to retrieve. If the result indicates it is indeterminate, then we
 * have to guess one for it.
 */
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../com/comhdr.h"

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

/*
 * if PATH_MAX is indeterminate, we have to guess one. We're not guaranteed this
 * is adequate.
 */
#define PATH_MAX_GUESS 1024
#define SUSV3 200112L

static long posix_version   = 0;
static char *path_alloc( int *size );

/* main program, testing driver */
int main( int argc, char **argv ) {
  int size;
  char *path = path_alloc( &size );
  int i;
  for ( i = 0; i < size; i += 256 ) {
    strcat( path, "/home/alex" );
  }
  printf( "path is: \n%s\nsize is %d\n", path, size );
  free( path );
  return 0;
}

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
