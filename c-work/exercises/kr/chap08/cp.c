/**
 * cp.c
 * implementation of cp *
 */
#include <fcntl.h>
#include <unistd.h>
#include "error.h"

int main( int argc, char **argv ) {
  int n, fd1,fd2, size = 128;
  char buf[ 128 ];

  if ( argc != 3 ) {
    error( "usgae: cp file1 file2" );
  }
  if ( (fd1 = open( *++argv, O_RDONLY, 0 )) == -1 ) {
    error( "open file %s", *argv );
  }
  if ( (fd2 = creat( *++argv, 0644 )) == -1 ) {
    error( "create file %s", *argv );
  }
  while ( (n = read( fd1, buf, size )) > 0 ) {
    if ( n != write( fd2, buf, n ) ) {
      error( "writing file %s", *argv );
    }
  }
  close( fd2 );
  close( fd1 );
  return 0;
}
