/*
 * eg0803.c
 * demo of wait.
 * and tricks about termination status.
 */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../com/comhdr.h"

static void pr_exit( int status ) {
  if ( WIFEXITED( status ) ) {
    printf( "Normal exited with exit code %d\n", WEXITSTATUS( status ) );
  } else if ( WIFSIGNALED( status ) ) {
    printf( "Abnormal terminated by signal number %d%s\n",
	WTERMSIG( status ),
#ifdef WCOREDUMP
	WCOREDUMP( status ) ? "(core dumped)" : "" );
#else
	"" );
#endif
  } else if ( WIFSTOPPED( status ) ) {
    printf( "Abnormal stopped by signal number %d\n",
	WSTOPSIG( status ) );
  }
}

int main( int argc, char **argv ) {
  pid_t pid;
  int status;
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    /* child process, we terminate with exit( 7 ) */
    exit( 7 ); /* terminate child process normally with exit code 7 */
  }
  /* wait for child to terminate and retrieve termination status about child */
  if ( wait( &status ) != pid ) {
    err_sys( "error on wait" );
  }
  pr_exit( status );

  /* Another child termination example, abnornal abort */
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    abort();
  }
  if ( wait( &status ) != pid ) {
    err_sys( "error on wait" );
  }
  pr_exit( status );

  /* Another one, stopped by kernel */
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    status /= 0; /* generate signal SIGFLP */
  }
  if ( wait( &status ) != pid ) {
    err_sys( "error on wait" );
  }
  pr_exit( status );

  return 0;
}
