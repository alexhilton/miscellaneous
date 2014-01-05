/**
 * eg0404.c
 * Use chmod to change the permissions of a file.
 */
#include <stdio.h>
#include <sys/stat.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  struct stat buf;
  /* turn on set-group id bit, and turn off group execution. */
  if ( stat( "foo", &buf ) < 0 ) {
    err_sys( "stat error on 'foo'" );
  }
  if ( chmod( "foo", (buf.st_mode & ~S_IXGRP) | S_ISGID ) < 0 ) {
    err_sys( "chmod error on 'foo'" );
  }
  /* set absolute mode 'rw-r--r--' to bar */
  if ( chmod( "bar", (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ) < 0 ) {
    err_sys( "chmod error on 'bar'" );
  }
  return 0;
}
