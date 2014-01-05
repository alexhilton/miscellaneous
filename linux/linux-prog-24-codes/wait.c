/*
 * wait.c
 *
 * a program deonstrates how to use wait().
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main( int argc, char *argv[] ) {
  pid_t pid;
  pid_t wpid; /* process ID from wait() */
  int status; /* exit status from wait() */

  pid = fork();

  if ( pid == -1 ) {
    perror( "fork()" );
    return 0;
  } else if ( pid == 0 ) {
    /* child process is a copy of its parent process */
    printf( "PID %ld: child started, parent is %ld\n", (long) getpid(),
	    (long) getppid() );
  } else {
    printf( "PID %ld: started child PID %ld\n", (long) getpid(), (long) pid );
    wpid = wait( &status );
    if ( wpid == -1 ) {
      perror( "wait()" );
      return 0;
    } else if ( wpid != pid ) {
      return 0;
    } else {
      printf( "child PID %ld exited status 0x%04X\n", (long) pid, status );
    }
  }

  return 0;
}
