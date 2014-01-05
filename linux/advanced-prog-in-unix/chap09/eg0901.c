/*
 * eg0901.c
 * Creating an orphaned process group.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "../com/comhdr.h"

static void sig_hup( int signo ) {
  printf( "SIGHUP received, pid = %d\n", getpid() );
}

static void pr_pids( char *name ) {
  printf( "%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
      name, getpid(), getppid(), getpgrp(), tcgetpgrp( STDIN_FILENO ) );
  fflush( stdout );
}

int main( int argc, char **argv ) {
  char ch;
  pid_t pid;

  pr_pids( "parent" );
  if ( (pid = fork()) < 0 ) {
    err_sys( "fork error" );
  } else if ( pid > 0 ) {
    sleep( 5 ); /* sleep to let child stop itself */
    exit( 0 );
  } else {
    pr_pids( "child" );
    signal( SIGHUP, sig_hup ); /* establish signal handler */
    kill( getpid(), SIGTSTP ); /* stop ourself */
    pr_pids( "child" );
    if ( read( STDIN_FILENO, &ch, 1 ) != 1 ) {
      printf( "read error from controlling TTY, errno = %d, %s\n", errno,
	  strerror( errno ) );
      exit( 0 );
    }
  }

  return 0;
}
