/**
 * eg0106.c
 * show you how to use strerror and errno
 */
#include <errno.h>
#include <stdio.h>

int main( int argc, char **argv ) {
  fprintf( stderr, "EACCES: %s\n", strerror( EACCES ) );

  errno = ENOTSUP;
  errno = ENOEXEC;
  perror( *argv );
  return 0;
}
