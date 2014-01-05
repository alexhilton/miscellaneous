/**
 * ex0304.c
 * Verify what will happen when closing one of two fds, one of which was duped
 * from another.
 * The result shows that closing a fd duped from another one doesnot affect the
 * original one.
 * If we redirect stdin, stdout and stderr (0, 1 and 2) to some other file,
 * whose fd is 5. We can write like this:
 *   dup2( 5, 0 );
 *   dup2( 5, 1 );
 *   dup2( 5, 2 );
 * Since we will use 0, 1 and 2 instead of 5, so we need to close 5. Then
 * original 0, 1 and 2 have been closed by dup2.
 * If fd is less than 3, say one of 0, 1 or 2, we don't have to close it.
 *   dup2( 1, 0 );
 *   dup2( 1, 1 );
 *   dup2( 1, 2 );
 * when dup2( 1, 1 ), it is not duped, so we cannot close it.
 */
#include <stdio.h>
#include <unistd.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  int fd;
  if ( (fd  = dup( STDOUT_FILENO )) < 0 ) {
    err_sys( "error while duping stdout" );
  }
  /* now we close fd */
  close( fd );
  /* see if we can write to stdout */
  char buf[] = "Hello, world\n";
  write( STDOUT_FILENO, buf, 13 );
  return 0;
}
