/*
 * ex0804.c
 * demo of interpreter file
 * Here we use execlp instead of execl. And the argv[2] of echoall is
 * './intertest', not its full path.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  setenv( "PATH", ".", 0 );
  pid_t pid;
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    /* the argv[2] of echoall will be relative path './intertest' not ab path */
    if ( execlp( "testinterp",
	  "testinterp", "myarg1", "MY ARG2", NULL ) < 0 ) {
      err_sys( "error on execl" );
    }
  }

  if ( waitpid( pid, NULL, 0 ) != pid ) {
    err_sys( "error on waitpid" );
  }

  return 0;
}
