/**
 * eg0403.c
 * show you how to set a file creation mode mask for a process.
 * All bits which are turned on in mask will be turned off when creating new
 * files.
 * A child's process mask value will never affect its parent. That is, you set a
 * mask value in your process, it will never affect its parent --- Shell.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../com/comhdr.h"

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP \
    | S_IWGRP | S_IROTH | S_IWOTH)

int main( int argc, char **argv ) {
  umask( 0 ); /* this will turn on all bits when creating file */
  if ( creat( "foo", RWRWRW ) < 0 ) {
    err_sys( "creat error on file foo" );
  }
  umask( S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
  if ( creat( "bar", RWRWRW ) < 0 ) {
    err_sys( "creat error on file bar" );
  }
  return 0;
}
