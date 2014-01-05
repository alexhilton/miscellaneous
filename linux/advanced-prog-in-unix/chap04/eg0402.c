/**
 * eg0402.c
 * Use system call access and open to test the accessibilities of a file.
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  if ( argc != 2 ) {
    err_quit( "Usage: prog file\n" );
  }
  if ( access( *++argv, R_OK ) < 0 ) {
    err_ret( "access error for %s", *argv );
  } else {
    printf( "read access OK\n" );
  }
  if ( open( *argv, O_RDONLY ) < 0 ) {
    err_ret( "open error for %s", *argv );
  } else {
    printf( "open for reading OK\n" );
  }
  return 0;
}
