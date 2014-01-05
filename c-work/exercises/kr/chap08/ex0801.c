/**
 * ex0801.c
 * implement cat with open, close, read and write of Linux API
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_SIZE 128 /* max size of bytes read and write once a time */

int main( int argc, char **argv ) {
  int fd;
  int n;
  char buf[ MAX_SIZE ];

  if ( argc == 1 ) {
    /* copy stdin to stdout */
    while ( (n = read( 0, buf, MAX_SIZE )) > 0 ) {
      if ( n != write( 1, buf, n ) ) {
	fprintf( stderr, "error while writing\n" );
      }
    }
  } else {
    while ( --argc > 0 ) {
      if ( (fd = open( *++argv, O_RDONLY, 0 )) == -1 ) {
	fprintf( stderr,  "error opening file %s\n", *argv );
	continue;
      }
      while ( (n = read( fd, buf, MAX_SIZE )) > 0 ) {
	if ( n != write( 1, buf, n ) ) {
	  fprintf( stderr, "erro while writing\n" );
	}
      }
      close( fd );
    }
  }
  return 0;
}
