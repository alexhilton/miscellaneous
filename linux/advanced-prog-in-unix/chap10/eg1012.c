/*
 * eg1012.c
 * protect critical region from signal using sigsuspend
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include "../com/comhdr.h"

/* print all the signals in currently signal mask */
static void pr_mask( const char *str );
static void sig_int( int signo );

int main( void ) {
  sigset_t newmask, oldmask, waitmask;

  pr_mask( "program start: " );

  if ( signal( SIGINT, sig_int ) == SIG_ERR ) {
    err_sys( "signal( SIGINT ) failed" );
  }

  sigemptyset( &waitmask );
  sigemptyset( &newmask );
  sigaddset( &newmask, SIGINT );
  sigaddset( &waitmask, SIGUSR1 );

  /* block SIGINT and save current signal mask */
  if ( sigprocmask( SIG_BLOCK, &newmask, &oldmask ) < 0 ) {
    err_sys( "SIG_BLOCK on SIGINT failed" );
  }

  /* critical region of code */
  pr_mask( " in critical region:" );

  /* pause, allowing all signals except SIGUSR1 */
  /*
   * sigsuspend: set waitmask as current signal mask, and pause, until a
   * signal(not in the mask) comes
   * It is the same to:
   * 	sigprocmask( setmask, &waitmask, NULL );
   * 	pause();
   * But sigsuspend is an atomic operation. If use sigprocmask and pause(),
   * chances are a signal might come after sigprocmask but before pause, then
   * the signal is lost
   */
  if ( sigsuspend( &waitmask ) != -1 ) {
    err_sys( "sigsuspend() error" );
  }
  pr_mask( "after return from sigsuspend: " );

  /* reset signal mask which unblocks SIGINT */
  if ( sigprocmask( SIG_SETMASK, &oldmask, NULL ) < 0 ) {
    err_sys( "SIG_SETMASK error " );
  }

  /* continue processing */
  return 0;
}

static void sig_int( int signo ) {
  pr_mask( "\n in sig_int: " );
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
  if ( sigismember( &sigset, SIGABRT ) ) {
    printf( "SIGABRT " );
  }
  if ( sigismember( &sigset, SIGCHLD ) ) {
    printf( "SIGCHLD " );
  }
  if ( sigismember( &sigset, SIGKILL ) ) {
    printf( "SIGKILL " );
  }
  if ( sigismember( &sigset, SIGSEGV ) ) {
    printf( "SIGSEGV " );
  }
  if ( sigismember( &sigset, SIGSTOP ) ) {
    printf( "SIGSTOP " );
  }
  if ( sigismember( &sigset, SIGTERM ) ) {
    printf( "SIGTERM " );
  }
  if ( sigismember( &sigset, SIGUSR2 ) ) {
    printf( "SIGUSR2 " );
  }
  if ( sigismember( &sigset, SIGTSTP ) ) {
    printf( "SIGTSTP " );
  }
  /* other signals goes here */
  printf( "\n" );
  errno = errno_save;
}
