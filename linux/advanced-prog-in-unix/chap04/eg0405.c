/**
 * eg0405.c
 * Filesystem, unlink.
 */
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  if ( open( "tmpfile", O_RDWR ) < 0 ) {
    err_sys( "opening file 'tmpfile' error" );
  }
  if ( unlink( "tmpfile" ) < 0 ) {
    err_sys( "error on unlink 'tmpfile'" );
  }
  printf( "'tmpfile' has been removed\n" );
  sleep( 15 );
  printf( "done\n" );
  return 0;
}
