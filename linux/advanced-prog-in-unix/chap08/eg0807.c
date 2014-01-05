/*
 * eg0807.c
 * demo of interpreter file
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  pid_t pid;
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    //if ( execl( "/home/alex/work/linux/advanced-prog-in-unix/chap08/testinterp", 
    if ( execl( "testinterp",
	  "testinterp", "myarg1", "MY ARG2", NULL ) < 0 ) {
      err_sys( "error on execl" );
    }
  }

  if ( waitpid( pid, NULL, 0 ) != pid ) {
    err_sys( "error on waitpid" );
  }

  return 0;
}
