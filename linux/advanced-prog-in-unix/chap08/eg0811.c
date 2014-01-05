/*
 * eg0811.c
 * program to generate an account data 
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  pid_t pid;

  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid != 0 ) { /* parent */
    sleep( 2 ); /* block 2 seconds */
    exit( 2 ); /* exit with code  2 */
  }
  /* first child */

  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid != 0 ) {
    /* first child */
    sleep( 4 );
    abort(); /* exit with core dump */
  }

  /* second child */
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid != 0 ) {
    /* second child */
    execl( "/bin/dd", "dd", "if=/etc/termcap", "of=/dev/null", NULL );
    exit( 7 );
  }

  /* third child */
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid != 0 ) {
    /* third child */
    sleep( 8 );
    exit( 0 );
  }

  /* fourth child */
  sleep( 6 );
  kill( getpid(), SIGKILL );
  exit( 6 );
}
