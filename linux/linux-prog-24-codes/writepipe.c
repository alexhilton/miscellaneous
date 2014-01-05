/*
 * writepipe.c
 *
 * a program demonstrates how to write things into a pipe.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>

int main( int argc, char *argv[] ) {
  struct passwd *pw = NULL;
  char cmd[ 256 ];
  FILE *p = NULL; /* mail pipe */
  long pid = (long) getpid();

  /*
   * If something unexpected occures the following method
   * will handle it.
   */
  signal( SIGPIPE, SIG_IGN );
  /* lookup our userid */
  if ( (pw = getpwuid( getuid() )) == NULL ) {
    perror( "getpwuid()" );
    return 1;
  }

  /* format command */
  sprintf( cmd, "mail -s 'A message from process ID %ld' %s",
	   pid, pw->pw_name );

  /* open a pipe to mail */
  if ( (p = popen( cmd, "w" )) == NULL ) {
    perror( cmd );
    return 1;
  }

  /* write our message */
  fprintf( p, "this is command %s speaking.\n", argv[ 0 ] );
  fprintf( p, "I am operating in the account for %s\n", pw->pw_gecos );

  if ( getuid() != 0 ) {
    fprintf( p, "I'd like to operate in root instead\n" );
    fprintf( p, "I could do more damage there. :)\n\n" );
  } else {
    fprintf( p, "I'd like to operate in a non-root ID instead.\n" );
    fprintf( p, "I would be safer there.\n" );
  }

  fprintf( p, "Sincerely, \n Process ID %ld\n", pid );

  if ( pclose( p ) != 0 ) {
    perror( "closing pipe" );
    return 0;
  } else {
    printf( "message sent to %s\n", pw->pw_name );
  }

  return 0;
}
