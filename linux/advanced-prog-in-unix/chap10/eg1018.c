/*
 * eg1018.c
 * An implementation of sleep() with signals
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "../com/comhdr.h"

static void sig_alrm( int singo );
unsigned int mysleep( unsigned int n );
static void sig_int( int signo );

int main( int argc, char **argv ) {
  /* test driver */
  if ( signal( SIGINT, sig_int ) == SIG_ERR ) {
    fprintf( stderr, "error on signal(SIGINT)\n" );
  }
  unsigned int n = mysleep( 5 );
  fprintf( stdout, "mysleep reutrns %u\n", n );
  return 0;
}

static void sig_int( int signo ) {
  printf( "SIGINT caught\n" );
}

static void sig_alrm( int signo ) {
  /* nothing to do, just returning wakes up sigsuspend() */
}

unsigned int mysleep( unsigned int nsecs ) {
  struct sigaction newact, oldact;
  sigset_t newmask, oldmask, suspmask;
  unsigned int unslept;

  /* set our handler, save previous information */
  newact.sa_handler = sig_alrm;
  sigemptyset( &newact.sa_mask );
  newact.sa_flags = 0;
  sigaction( SIGALRM, &newact, &oldact );

  /* block SIGALRM and save current signal mask */
  sigemptyset( &newmask );
  sigaddset( &newmask, SIGALRM );
  sigprocmask( SIG_BLOCK, &newmask, &oldmask );

  alarm( nsecs );

  suspmask = oldmask;
  /* make sure SIGALRM isn't blocked */
  sigdelset( &suspmask, SIGALRM );
  /* wait for any signal to be caught */
  sigsuspend( &suspmask );

  /* some signal has been caught, SIGALRM is now blocked */
  unslept = alarm( 0 );
  sigaction( SIGALRM, &oldact, NULL ); /* reset previous action */

  /* reset signal mask, which unblocks SIGALRM */
  sigprocmask( SIG_SETMASK, &oldmask, NULL );

  return unslept;
}
