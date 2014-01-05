/*
 * eg1019.c
 * Implement job control using signals: SIGCONT, SIGTSTP, SIGTOU and SIGSTOP
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "../com/comhdr.h"
#define BUFSIZE 1024
static void sig_tstp( int signo );

int main( int argc, char **argv ) {
  int n;
  char buf[ BUFSIZE ];

  /* Only catch SIGTSTP if we're running with a job-control shell */
  /* Only a job-control shell will set handler of SIGTSTP as SIG_DFL */
  /* And we should use our handler only in a job-control shell */
  if ( signal( SIGTSTP, SIG_IGN ) == SIG_DFL ) {
    signal( SIGTSTP, sig_tstp );
  }

  while ( (n = read( STDIN_FILENO, buf, BUFSIZE )) > 0 ) {
    if ( write( STDOUT_FILENO, buf, n) != n ) {
      err_sys( "write error" );
    }
  }

  if ( n < 0 ) {
    /* read failed */
    err_sys( "read error" );
  }

  return 0;
}

/* signal handler for SIGTSTP */
static void sig_tstp( int signo ) {
  sigset_t mask;

  /* ... move cursor to lower left corner, reset tty mode ... */
  /*
   * When we receive this signal the user want to run another program, so we
   * should reset the terminal to what it was before we ran.
   */

  /* unblock SIGTSTP, since it is blocked while we are handling it */
  sigemptyset( &mask );
  sigaddset( &mask, SIGTSTP );
  sigprocmask( SIG_UNBLOCK, &mask, NULL );

  /* reset disposition to default */
  signal( SIGTSTP, SIG_DFL );

  /* send the signal to ourself */
  kill( getpid(), SIGTSTP );

  /* we won't return from the kill until we are continued */
  /* reestablish signal hanlder */
  signal( SIGTSTP, sig_tstp );

  /* ...reset tty mode, redraw screen... */
}
