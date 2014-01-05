/*
 * eg1003.c
 * catch the SIGCHLD signal.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../com/comhdr.h"

static void sig_cld( int signo );

int main( int argc, char **argv ) {
  pid_t pid;

  if ( signal( SIGCHLD, sig_cld ) == SIG_ERR ) {
    err_sys( "error on establishing signal handler for SIGCHLD" );
  }
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    sleep( 2 );
    _exit( 0 );
  }

  pause();
  return 0;
}

static void sig_cld( int signo ) {
  int status;
  pid_t pid;
  printf( "signal SIGCHLD received\n" );
  if ( signal( SIGCHLD, sig_cld ) == SIG_ERR ) {
    err_sys( "error on establishing signal handler for SIGCHLD" );
  }
  if ( (pid = wait( &status )) < 0 ) {
    err_sys( "error on wait" );
  }
  printf( "pid = %d\n", pid );
}
