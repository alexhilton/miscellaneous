/*
 * eg1009.c
 * an usage of sigprocmask.
 * and some setttings of signal
 * From the running result of this program:
 * [alex@localhost chap10]$ ./a.out 
 *  ^\^\^\^\^\^\^\
 *  SIGQUIT pending # this is output after 5 seconds of sleeping
 *  caught SIGQUIT
 *  SIGQUIT unblocked # when it SIGQUIT is unblocked(sigprocmask(SIG_SETMASK))
 *  		      # terminate the program
 *  ^\Quit
 * From the running result of this program we can see that during the sleep
 * after blocking SIGQUIT, it is blocked and pending until it is unblocked with
 * sigprocmask. Another observation is that multiple signal only be delivered
 * once.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../com/comhdr.h"

static void sig_quit( int signo );

int main( void ) {
  sigset_t newmask, oldmask, pendmask;

  if ( signal( SIGQUIT, sig_quit ) == SIG_ERR ) {
    err_sys( "cannot catch SIGQUIT" );
  }

  sigemptyset( &newmask );
  sigaddset( &newmask, SIGQUIT );

  /* block SIGQUIT and save current signal mask */
  /*
   * Here, we don't need to initialize oldmask and pendmask. Because sigprocmask
   * and sigpending operates on the whole signal set, not just adding one signal
   * or removing other signal. As a result, we don't have to initialize it. This
   * is different from newmask, for newmask we have to initialize it because we
   * add only one signal into the set.
   */
  if ( sigprocmask( SIG_BLOCK, &newmask, &oldmask ) < 0 ) {
    err_sys( "SIG_BLOCK error" );
  }

  /* SIGQUIT here will remain pending */
  sleep( 5 );

  /* Verify whether sigprocmask succeeds, or whether SIGQUIT is blocked */
  /* get the pending signal set */
  if ( sigpending( &pendmask ) < 0 ) {
    err_sys( "sigpending error" );
  }
  /* 
   * see whether SIGQUIT is pending: pendmask is the signal set that are
   * pending, so if SIGQUIT is pending--our previous sigprocmask works--it
   * should be in pendmask
   */
  if ( sigismember( &pendmask, SIGQUIT ) ) {
    printf( "\nSIGQUIT pending\n" );
  }

  /* reset signal mask which unblocks SIGQUIT */
  if ( sigprocmask( SIG_SETMASK, &oldmask, NULL ) < 0 ) {
    err_sys( "SIG_SETMASK error" );
  }
  printf( "SIGQUIT unblocked\n" );

  /* SIGQUIT here will terminate with core file */
  sleep( 5 );

  return 0;
}

static void sig_quit( int signo ) {
  printf( "caught SIGQUIT\n" );
  if ( signal( SIGQUIT, SIG_DFL ) == SIG_ERR ) {
    err_sys( "cannot reest SIGQUIT" );
  }

  return; /* why ? */
}
