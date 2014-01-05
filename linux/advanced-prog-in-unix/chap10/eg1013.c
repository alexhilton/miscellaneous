/*
 * eg1013.c
 * wait for a global variable to set by a signal handler using sigsuspend
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../com/comhdr.h"

volatile sig_atomic_t quitflag; /* set nonzero by signal handler */

/* one signal handler for SIGINT and SIGQUIT */
static void sig_int( int signo );

int main( void ) {
  sigset_t newmask, oldmask, zeromask;

  if ( signal( SIGINT, sig_int ) == SIG_ERR ) {
    err_sys( "signal(SIGINT) error" );
  }
  if ( signal( SIGQUIT, sig_int ) == SIG_ERR ) {
    err_sys( "signal(SIGQUIT) error" );
  }

  sigemptyset( &zeromask );
  sigemptyset( &newmask );
  sigaddset( &newmask, SIGQUIT );

  /* Block SIGQUIT and save current signal mask */
  if ( sigprocmask( SIG_BLOCK, &newmask, &oldmask ) < 0 ) {
    err_sys( "SIG_BLOCK error" );
  }

  /*
   * We wait until quitflag is set
   * This is a little bit similar to wait and notify method in Java
   * while ( quitflag == 0 ) {
   * 	wait();
   * }
   */
  while ( quitflag == 0 ) {
    /* block no signals, just wait until quitflag is set */
    /*
     * Either signal SIGINT or SIGQUIT can stop suspending, but only SIGQUIT can
     * break the while loop, handler of SIQQUIT set quitflag as 1
     */
    sigsuspend( &zeromask );
  }

  /* SIGQUIT has been caught and is now blocked, do whatever */
  quitflag = 0;

  /* reset signal mask which unblocks SIGQUIT */
  if ( sigprocmask( SIG_SETMASK, &oldmask, NULL ) < 0 ) {
    err_sys( "SIG_SETMASK error" );
  }

  return 0;
}

static void sig_int( int signo ) {
  if ( signo == SIGINT ) {
    printf( "\ninterrupt\n" );
  } else if ( signo == SIGQUIT ) {
    quitflag = 1; /* set the flag for main loop */
  }
}
