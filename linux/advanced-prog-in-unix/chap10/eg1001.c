/*
 * eg1001.c
 * demo of signal handler
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../com/comhdr.h"

static void sig_usr( int );

int main( int argc, char **argv ) {
  if ( signal( SIGUSR1, sig_usr ) == SIG_ERR ) {
    err_sys( "cannot catch signal SIGUSER1" );
  }
  if ( signal( SIGUSR2, sig_usr ) == SIG_ERR ) {
    err_sys( "cannot catch signal SIGUSER2" );
  }

  while ( 1 ) {
    pause();
  }
  return 0;
}

static void sig_usr( int signo ) {
  if ( signo == SIGUSR1 ) {
    printf( "catch signal SIGUSER1\n" );
  } else if ( signo == SIGUSR2 ) {
    printf( "catch signal SIGUSER2\n" );
  } else {
    err_dump( "received signal %d\n", signo );
  }
}
