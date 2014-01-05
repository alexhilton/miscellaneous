/**
 * eg0401.c
 * use struct stat and macros S_ISDIR etc to determine the type of a file.
 * The filenames are  passed from command line arguments.
 * we will print file name followed by its file type.
 * The file type is one of regular file, directory, character special, block
 * special, FIFO & pipe or socket.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  char *p;
  struct stat buf;

  while ( --argc ) {
    printf( "%s: ", *++argv );
    if ( lstat( *argv, &buf ) < 0 ) {
      err_ret( "lstat error" );
      continue;
    }
    if ( S_ISDIR( buf.st_mode ) ) {
      p = "directory";
    } else if ( S_ISREG( buf.st_mode ) ) {
      p = "regular file";
    } else if ( S_ISCHR( buf.st_mode ) ) {
      p = "character special";
    } else if ( S_ISBLK( buf.st_mode ) ) {
      p = "block special";
    } else if ( S_ISFIFO( buf.st_mode ) ) {
      p = "FIFO";
    } else if ( S_ISSOCK( buf.st_mode ) ) {
      p = "socket";
    } else if ( S_ISLNK( buf.st_mode ) ) {
      p = "symbolic link";
    } else {
      p = "unknown type";
    }
    printf( "%s\n", p );
  }
  return 0;
}
