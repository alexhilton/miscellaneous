/*
 * eg1010.c
 * an implementation of signal using sigaction
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../com/comhdr.h"

typedef void Sigfunc( int );

Sigfunc *mysignal( int signo, Sigfunc *func ) {
  struct sigaction act, oldact;
  act.sa_handler = func;
  sigemptyset( &act.sa_mask );
  act.sa_flags = 0;
  if ( signo == SIGALRM ) {
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
  } else {
#ifdef SA_RESTART
    act.sa_flags |= SA_RESTART;
#endif
  }

  if ( sigaction( signo, &act, &oldact ) < 0 ) {
    return SIG_ERR;
  }
  return oldact.sa_handler;
}


/* 
 * Another implementation which stops interrupted system calls from restarting
 */
Sigfunc *signal_intr( int signo, Sigfunc *func ) {
  struct sigaction act, oldact;
  act.sa_handler = func;
  sigemptyset( &act.sa_mask );
  act.sa_flags = 0;
#ifdef SA_INTERRUPT
  act.sa_flags |= SA_INTERRUPT;
#endif
  if ( sigaction( signo, &act, &oldact ) < 0 ) {
    return SIG_ERR;
  }

  return oldact.sa_handler;
}

static void sig_quit( int signo );

/* main program testing driver */
int main( int argc, char **argv ) {
  if ( mysignal( SIGQUIT, sig_quit ) == SIG_ERR ) {
    err_sys( "error on setting handler for SIGQUIT" );
  }

  sleep( 5 ); /* give some time for user to generate SIGQUIT */

  if ( signal_intr( SIGQUIT, sig_quit ) == SIG_ERR ) {
    err_sys( "error on setting handler for SIGQUIT" );
  }

  sleep( 5 );

  return 0;
}

static void sig_quit( int signo ) {
  printf( "signal SIGQUIT caught\n" );
}
