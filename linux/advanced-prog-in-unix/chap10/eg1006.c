/*
 * eg1006.c
 * another alternative using alarm to terminate a blocked process
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "../com/comhdr.h"

static void sig_alrm( int signo );
static jmp_buf alrm_buf;

int main( int argc, char **argv ) {
  int n;
  char line[ MAXLINE ];

  if ( signal( SIGALRM, sig_alrm ) == SIG_ERR ) {
    err_sys( "signal( SIGALRM ) error" );
  }
  /* setjmp( n ) return non-zero if it is returned from longjmp() */
  if ( setjmp( alrm_buf ) != 0 ) {
    err_quit( "read timeout" );
  }
  alarm( 10 );
  if ( (n = read( STDIN_FILENO, line, MAXLINE )) < 0 ) {
    err_sys( "read from stdin error" );
  }
  alarm( 0 );
  write( STDOUT_FILENO, line, n );

  return 0;
}

static void sig_alrm( int singo ) {
  longjmp( alrm_buf, 1 );
}
