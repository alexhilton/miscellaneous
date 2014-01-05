/*
 * fork1.c
 *
 * A program demonstrates how to use function fork() 
 * combine with system().
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

int main( int argc, char *argv[] ) {
  pid_t pid;
  pid = fork(); /* create a new child process */

  if ( pid == -1 ) {
    perror( "failed to fork()" );
    return 1;
  } else if ( pid == 0 ) {
    printf( "PID %ld: child started, parent is %ld\n", (long) getpid(),
	    (long) getppid() );
    system( "ps f" );
  } else {
    printf( "PID %ld: started child PID %ld\n", (long) getpid(), (long) pid );
  }

  sleep( 1 ); /* wait for a second */

  return 0;
}
