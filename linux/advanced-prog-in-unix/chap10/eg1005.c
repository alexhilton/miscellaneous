/*
 * eg1005.c
 * This example demonstrates another  usage of alarm/pause -- to terminate some
 * blocked process due to some slow operation. Reading or writing a very slow
 * devices, for instace, should be terminated after a specified timer expired.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../com/comhdr.h"

static void sig_alrm( int signo );

int main( int argc, char **argv ) {
  int n;
  char line[ MAXLINE ];

  /*
   * If you comment out the following registering handler for SIGALRM, the
   * process will be terminated when 10 is expired
   */
  /*
  if ( signal( SIGALRM, sig_alrm ) == SIG_ERR ) {
    err_sys( "signal( SIGALRM ) error" );
  }*/
  alarm( 10 );

  if ( (n = read( STDIN_FILENO, line, MAXLINE )) < 0 ) {
    err_sys( "read error" );
  }
  alarm( 0 );
  write( STDOUT_FILENO, line, n );
  return 0;
}


static void sig_alrm( int signo ) {
  return; /* nothing to do, just return to interrupt the read */
}
