/*
 * eg1004.c
 * an bare bone implementation of function sleep with raise and alarm
 * and pause.
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "../com/comhdr.h"

static void sig_alrm( int signo ) {
  return; /* nothing to do, just return to wake up the pause */
}

/*
 * sleep until nsec elapsed.
 * returning 0 if nsec has been elapsed or the seconds left, if the process is
 * interrupted.
 */
unsigned int sleep1( unsigned int nsecs ) {
  if ( signal( SIGALRM, sig_alrm ) == SIG_ERR ) {
    return nsecs;
  }
  alarm( nsecs ); /* start the timer */
  pause(); /* next caught signal wakes us up */

  return alarm( 0 ); /* turn off timer, return unslept time */
}

/*
 * another imperfect implementation.
 */
static jmp_buf env_alrm;
static void sig_alrm2( int signo ) {
  /* 
   * we will jump back to where env_alrm is set -- setjmp(env_alrm)
   * 1 is the return value of setjmp()
   */
  longjmp( env_alrm, 1 );
}

unsigned int sleep2( unsigned int nsecs ) {
  if ( signal( SIGALRM, sig_alrm2 ) == SIG_ERR ) {
    return nsecs;
  }
  /*
   * setjmp will return 0 if we call it directly, it return what longjmp set
   * when jumping from longjmp
   */
  if ( setjmp( env_alrm ) == 0 ) {
    alarm( nsecs ); /* start the timer */
    pause(); /* next caught signal wakes us upp */
  }
  return alarm( 0 );
}

static void sig_int( int signo );

/* main program: test driver */
int main( int argc, char **argv ) {
  unsigned int unslept;
  if ( signal( SIGINT, sig_int ) == SIG_ERR ) {
    err_sys( "signal(SIGINT) error" );
  }
  unslept = sleep2( 5 );
  printf( "sleep2 returned; %u\n", unslept );

  return 0;
}

static void sig_int( int signo ) {
  int i;
  volatile int j;
  printf( "\nsign_int starting\n" );
  for ( i = 0; i < 2000000; i++ ) {
    j += i * i;
  }
  printf( "sig_int finished\n" );
}

