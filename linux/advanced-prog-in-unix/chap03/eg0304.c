/**
 * eg0304.c
 * Print file flags for specified descriptors.
 */
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  int accmode, val;

  if ( argc != 2 ) {
    err_quit( "Usage: eg0303 <descriptor#>" );
  }

  if ( (val = fcntl( atoi( *++argv ), F_GETFL, 0 )) < 0 ) {
    err_sys( "fcntl error for fd %d\n", atoi( *argv ) );
  }

  accmode = val & O_ACCMODE;
  if ( accmode == O_RDONLY ) {
    printf( "read only" );
  } else if ( accmode == O_WRONLY ) {
    printf( "write only" );
  } else if ( accmode == O_RDWR ) {
    printf( "read write" );
  } else {
    err_dump( "unknown access mode" );
  }

  /* I prefer '(val & O_APPEND) == O_APPEND', which is much clearer */
  if ( val & O_APPEND ) {
    printf( ", append" );
  }
  if ( val & O_NONBLOCK ) {
    printf( ", nonblocking" );
  }
#if !defined( _POSIX_C_SOURCE ) && defined( O_SYNC )
  if ( val & O_SYNC ) {
    printf( ", synchronous writes" );
  }
#endif
  putchar( '\n' );
  return 0;
}
