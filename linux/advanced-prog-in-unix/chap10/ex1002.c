/*
 * ex1002.c
 * implement mysig2str
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "../com/comhdr.h"

static int mysig2str( int signo, char *name );
static void sig_handler( int signo );

int main( int argc, char **argv ) {
  if ( signal( SIGALRM, sig_handler ) == SIG_ERR ) {
    err_sys( "signal( sigalarm, errror  ) " );
  }
  if ( signal( SIGINT, sig_handler ) == SIG_ERR ) {
    err_sys( "signal( sigint, errror  ) " );
  }
  if ( signal( SIGUSR1, sig_handler ) == SIG_ERR ) {
    err_sys( "signal( siguser1, errror  ) " );
  }
  if ( signal( SIGUSR2, sig_handler ) == SIG_ERR ) {
    err_sys( "signal( siguser2, errror  ) " );
  }
  alarm( 2 );
  while ( 1 ) {
    pause();
  }

  return 0;
}

static void sig_handler( int signo ) {
  char name[ 1024 ];
  mysig2str( signo, name );
  printf( "caught signal %s\n", name );
}

static int mysig2str( int signo, char *name ) {
  switch ( signo ) {
  case SIGKILL:
    strcpy( name, "KILL" );
    break;
  case SIGALRM:
    strcpy( name, "ALRM" );
    break;
  case SIGUSR1:
    strcpy( name, "USR1" );
    break;
  case SIGUSR2:
    strcpy( name, "USR2" );
    break;
  case SIGQUIT:
    strcpy( name, "QUIT" );
    break;
  case SIGCONT:
    strcpy( name, "CONT" );
    break;
  case SIGINT:
    strcpy( name, "INT" );
    break;
  default:
    strcpy( name, "UNKNOWN" );
    return -1;
  }
  return 0;
}
