/**
 * eg0101.c
 * example 0101 of Book <Advanced Programming in UNIX environment>
 * a simple implementation of command ls: listing all contents in a directory.
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  DIR *dp;
  struct dirent *dirp;

  if ( argc != 2 ) {
    err_quit( "Usage: ls dir1 [dir2] [dir3]" );
  }

  if ( (dp = opendir( *++argv )) == NULL ) {
    /* open failed */
    err_sys( "cann't open %s", *argv );
  }
  while ( (dirp = readdir( dp )) != NULL ) {
    fprintf( stdout, "%s\n", dirp->d_name );
  }

  closedir( dp );
  return 0;
}
