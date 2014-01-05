/*
 * eg1008.c
 * print the signal mask for a process
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "../com/comhdr.h"

void pr_mask( const char *str ) {
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

int main( int argc, char **argv ) {
  /* test driver */
  char str[ 128 ];
  sprintf( str, "signal mask for process: %d\n", getpid() );
  pr_mask( str );
  return 0;
}
