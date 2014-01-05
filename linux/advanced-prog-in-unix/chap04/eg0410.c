/**
 * eg0410.c
 * Show you how to obtain the major and minor number of  a device.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  struct stat buf;

  while ( --argc > 0 ) {
    printf( "%s: ", *++argv );
    if ( lstat( *argv, &buf ) < 0 ) {
      err_sys( "error on stating %s", *argv );
      continue;
    }
    printf( "dev = %d/%d", major( buf.st_dev ), minor( buf.st_dev ) );
    if ( S_ISCHR( buf.st_mode ) || S_ISBLK( buf.st_mode ) ) {
      printf( " (%s) rdev = %d/%d",
	  (S_ISCHR(buf.st_mode) ? "character" : "block"), 
	  major( buf.st_rdev ), minor( buf.st_rdev ) );
    }
    printf( "\n" );
  }
  return 0;
}
