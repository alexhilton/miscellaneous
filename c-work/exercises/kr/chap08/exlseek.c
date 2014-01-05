/**
 * exlseek.c
 * exercise  lseek 
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "error.h"

/* write 128 bytes of chars on begin of argv[ 1 ] to end of it */
int main( int argc, char **argv ) {
  int fd;
  int size = 128;
  char buf[ 128 ];
  int n;
  if ( argc != 2 ) {
    error( "no input" );
  }
  if ( (fd = open( *++argv, O_RDWR, 0644 )) == -1 ) {
    error( "error opening file %s", *argv );
  }

  /* read size bytes on begin of file */
  /* jump to begin of file */
  lseek( fd, 0L, 0 ); /* this is redundent */
  if ( (n = read( fd, buf, size )) > 0 ) {
    /* jump to end of file */
    lseek( fd, 0l, 2 );
    if ( n != write( fd, buf, n ) ) {
      error( "writing file %s", *argv );
    }
  }

  /* and display the result to stdout */
  lseek( fd, 0L, 0 ); /* jump to begin of file */
  while ( (n = read( fd, buf, size )) >  0 ) {
    if ( n != write( 1, buf, n ) ) {
      error( "writing file %s to stdout", *argv );
    }
  }
  close( fd );
  return 0;
}
