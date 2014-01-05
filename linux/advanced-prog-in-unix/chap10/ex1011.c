/**
 * eg0303.c
 * copy standard input to standard output.
 */
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/resource.h>
#include "../com/comhdr.h"

/* 
 * it is said that the size of BUFSIZE will affect the efficiency of the program
 * 
 */
#define BUFSIZE 100
static void sig_xfsz( int singo );

int main( int argc, char **argv ) {
  int n, write_size;
  char buf[ BUFSIZE ];

  if ( signal( SIGXFSZ, sig_xfsz ) == SIG_ERR ) {
    err_sys( "signal(SIGXFSZ) error" );
  }
  /* Modify RLIMIT_FSIZE to 1024 */
  struct rlimit limit;
  getrlimit( RLIMIT_FSIZE, &limit );
  limit.rlim_cur = 1024;
  setrlimit( RLIMIT_FSIZE, &limit );
  while ( (n = read( STDIN_FILENO, buf, BUFSIZE )) > 0 ) {
    if ( (write_size = write( STDOUT_FILENO, buf, n )) != n ) {
      err_sys( "write error, only wrote %d bytes", write_size );
    }
  }

  if ( n < 0 ) {
    err_sys( "read error" );
  }
  return 0;
}

static void sig_xfsz( int signo ) {
  printf( "SIGXFSZ caught\n" );
}
