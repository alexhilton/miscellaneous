/**
 * append.c
 * append files into first one on command line arguments and display the first file onto
 * screen.
 */
#include <unistd.h>
#include <fcntl.h>
#include "error.h"

#define MAX_SIZE 128

int main( int argc, char **argv ) {
  int fd1, fd2, n;
  char buf[ MAX_SIZE ];

  /* if there is no command line arguments, copy the stdin to stdout */
  if ( argc < 2 ) {
    while ( (n = read( 0, buf, MAX_SIZE )) > 0 ) {
      if ( n != write( 1, buf, n ) ) {
	error( "writing to stdout" );
      }
    }
  } else {
    /* open first file and jump to end of it */
    if ( (fd1 = open( *++argv, O_RDWR, 0644 )) == -1 ) {
      error( "open file %s", *argv );
    }
    /* jump to end of it */
    lseek( fd1, 0L, 2 );

    /* open other files and append it to fd1 */
    while ( *++argv != NULL ) {
      if ( (fd2 = open( *argv, O_RDONLY, 0 )) == -1 ) {
	error( "open file %s", *argv );
      }
      while ( (n = read( fd2, buf, MAX_SIZE )) > 0 ) {
	if ( n != write( fd1, buf, n ) ) {
	  error( "write file %s", *argv );
	}
      }
      close( fd2 );
    }

    /* jump to begin of fd1 */
    lseek( fd1, 0L, 0 );
    while ( (n = read( fd1, buf, MAX_SIZE )) > 0 ) {
      if ( n != write( 1, buf, n ) ) {
	error( "writing to stdout" );
      }
    }
    close( fd1 );
  }
  return 0;
}
