/*
 * eg1015.c
 * An implementation abort() with signals
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../com/comhdr.h"

void myabort();
static void sig_abrt( int signo );

int main( void ) {
  /* test driver */
  if ( signal( SIGABRT, sig_abrt ) == SIG_ERR ) {
    err_sys( "signal( SIGABRT ) error" );
  }
  myabort();

  return 0;
}

static void sig_abrt( int signo ) {
  printf( "SIGABRT caught\n" );
}

void myabort( void ) {
  sigset_t mask;
  struct sigaction action;

  /* caller can't ignore SIGABRT, if so, reset to default */
  sigaction( SIGABRT, NULL, &action ); /* get current sigaction */
  if ( action.sa_handler == SIG_IGN ) {
    action.sa_handler = SIG_DFL;
    sigaction( SIGABRT, &action, NULL ); /* set the action */
  }
  if ( action.sa_handler == SIG_DFL ) {
    fflush( NULL ); /* flush all open stdio streams */
  }

  /* caller cann't block SIGABRT, make sure it is unblocked */
  sigfillset( &mask );
  sigdelset( &mask, SIGABRT ); /* mask has only SIGABRT turned off */
  /* block all except SIGABRT */
  sigprocmask( SIG_SETMASK, &mask, NULL ); /* no checking for failure */
  kill( getpid(), SIGABRT ); /* send the signal */

  /* If we're here, process caught SIGABRT and returned */
  fflush( NULL );
  action.sa_handler = SIG_DFL;
  sigaction( SIGABRT, &action, NULL ); /* reset to default */

  /* block again and send signal once more, just in case */
  sigprocmask( SIG_SETMASK, &mask, NULL );
  kill( getpid(), SIGABRT );

  exit( 1 ); /* this should never be executed */
}
