/*
 * eg1011.c
 * An example of signal setting, sigsetjmp and setlongjmp.
 */
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include "../com/comhdr.h"

/* 
 * It is so obscure if you declare two function in a line like this:
 * 	static void sig_usr1( int signo ), sig_alrm( int signo )
 * But you know, functions, like variables, can be declared in a line
 */
static void sig_usr1( int signo );
static void sig_alrm( int signo );
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjmp;
static void pr_mask( const char *str );

int main( int argc, char **argv ) {
  if ( signal( SIGUSR1, sig_usr1 ) == SIG_ERR ) {
    err_sys( "error on setting handler for SIGUSR1" );
  }
  if ( signal( SIGALRM, sig_alrm ) == SIG_ERR ) {
    err_sys( "error on setting handler for SIGUSR1" );
  }
  pr_mask( "starting main: " );

  if ( sigsetjmp( jmpbuf, 1 ) ) {
    pr_mask( "ending main: " );
    exit( EXIT_SUCCESS );
  }

  canjmp = 1; /* now sigsetjmp is ok */

  for ( ; ; ) {
    pause();
  }

  return 0;
}

static void sig_usr1( int signo ) {
  time_t start_time;
  if ( canjmp == 0 ) {
    return;
  }
  pr_mask( "stating sig_usr1(): " );
  alarm( 3 );

  start_time = time( NULL );
  for ( ; ; ) {
    if ( time( NULL ) > start_time + 5 ) {
      break;
    }
  }
  pr_mask( "finishing sig_usr1(): " );
  canjmp = 0;
  siglongjmp( jmpbuf, 1 ); /* jump back to main, don't return */
}

static void sig_alrm( int signo ) {
  pr_mask( "in sig_alrm(): " );
  return;
}

static void pr_mask( const char *str ) {
  sigset_t sigset;
  int errno_save;

  errno_save = errno; /* we can be called by signal handlers */
  if ( sigprocmask( 0, NULL, &sigset ) < 0 ) {
    err_sys( "sigprocmask error" );
  }
  printf( "%s", str );
  if ( sigismember( &sigset, SIGINT ) ) {
    printf( "SIGINT " );
  }
  if ( sigismember( &sigset, SIGQUIT ) ) {
    printf( "SIGQUIT " );
  }
  if ( sigismember( &sigset, SIGUSR1 ) ) {
    printf( "SIGUSR1 " );
  }
  if ( sigismember( &sigset, SIGALRM ) ) {
    printf( "SIGALRM " );
  }
  /* other signals goes here */
  printf( "\n" );
  errno = errno_save;
}
