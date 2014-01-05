/**
 * eg0406.c
 * Show you how to use utime function.
 * In this example we first get the last access time and last modified time,
 * then truncate a file's length to 0, then reset the file's last access time
 * and last modified time to its original times. But the last change-status
 * time does change.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <stdio.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  struct stat statbuf;
  struct utimbuf timebuf;

  while ( --argc > 0 ) {
    /* fetch current times */
    if ( stat( *++argv, &statbuf ) < 0 ) { 
      err_sys( "%s: stat error", *argv );
      continue;
    }
    /* truncate the file */
    if ( open( *argv, O_RDWR | O_TRUNC ) < 0 ) {
      err_ret( "%s: open error", *argv );
      continue;
    }
    timebuf.actime = statbuf.st_atime;
    timebuf.modtime = statbuf.st_mtime;
    /* reset the times */
    if ( utime( *argv, &timebuf ) < 0 ) {
      err_sys( "%s: utime error", *argv );
    }
  }
  return 0;
}
