/*
 * eg0806.c
 * demos of execlp and execle.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../com/comhdr.h"

static char *env_init[] = { "USER=unknown", "TEMP=/tmp", NULL };

int main( int argc, char **argv ) {
  pid_t pid;

  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    execle( "/home/alex/work/linux/advanced-prog-in-unix/chap08/echoall",
	"echoall", "My arg1", "My arg2", NULL, env_init );
  }
  if ( waitpid( pid, NULL, 0 ) != pid ) {
    err_sys( "error on waitpid" );
  }

  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    if ( execlp( "echoall", "echoall", "only 1 arg", NULL ) < 0 ) {
      err_sys( "error on execlp" );
    }
  }

  return 0;
}
