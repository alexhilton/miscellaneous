/*
 * eg1001.c
 * demo of signal handler
 * We delete the while loop in main program and see what will happen
 * Prediction: if you delete loop while, the program will terminate immediately
 * when it receive the signal, any signal.
 * I cann't tell why, you have to press ENTER, after send a signal to this
 * program. It has stopped, but you have to press ENTER to make it quit
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../com/comhdr.h"

static void sig_usr( int );

int main( int argc, char **argv ) {
  if ( signal( SIGUSR1, sig_usr ) == SIG_ERR ) {
    err_sys( "cannot catch signal SIGUSER1" );
  }
  if ( signal( SIGUSR2, sig_usr ) == SIG_ERR ) {
    err_sys( "cannot catch signal SIGUSER2" );
  }

  /* while ( 1 ) { */
    pause();
  /* } */
  return 0;
}

static void sig_usr( int signo ) {
  if ( signo == SIGUSR1 ) {
    printf( "catch signal SIGUSER1\n" );
  } else if ( signo == SIGUSR2 ) {
    printf( "catch signal SIGUSER2\n" );
  } else {
    err_dump( "received signal %d\n", signo );
  }
}
