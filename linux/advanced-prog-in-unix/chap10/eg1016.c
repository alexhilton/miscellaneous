/*
 * eg1016.c
 * Use system() to invoke editor 'ed'
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../com/comhdr.h"

static void sig_int( int signo );
static void sig_chld( int signo );
int mysystem( const char *cmd );

int main( int argc, char **argv ) {
  int status;

  if ( signal( SIGINT, sig_int ) == SIG_ERR ) {
    err_sys( "signal(SIGINT) error" );
  }
  if ( signal( SIGCHLD, sig_chld ) == SIG_ERR ) {
    err_sys( "signal(SIGCHLD) error" );
  }
  if ( (status = mysystem( "/bin/ed" )) < 0 ) {
    err_sys( "error on system()" );
  }

  return 0;
}

static void sig_int( int signo ) {
  printf( "caught SIGINT\n" );
}

static void sig_chld( int signo ) {
  printf( "caught SIGCHLD\n" );
}
