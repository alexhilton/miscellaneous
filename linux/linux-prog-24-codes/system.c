/*
 * system.c
 *
 * A program demonstrates the using process of function system().
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>

int main( int argc, char *argv[] ) {
  struct passwd *pw = NULL;
  char cmd[ 256 ];
  int rc;
  long pid = (long) getpid();

  /* lookup for userid */
  if ( (pw = getpwuid( getuid() )) == NULL ) {
    perror( "getpwuid()" );
    return 0;
  }

  /* format command */
  sprintf( cmd, "ps f | mail -s 'PID %ld' %s", pid, pw->pw_name );

  /* run the command */
  errno = 0; /* for system() error checking */
  rc = system( cmd );

  /*
   * the return code of system() is complicated
   * we can use it and errno to check if error occurs.
   */
  if ( rc == 127 && errno != 0 ) {
    /* command failed to start */
    perror( cmd );
  } else if ( rc == -1 ) {
    /* other error occured */
    perror( cmd );
  } else {
    /* everything is OK */
    printf( "command '%s'\n returned code %d\n", cmd, rc );
    printf( "check your mail\n" );
  }

  return 0;
}
