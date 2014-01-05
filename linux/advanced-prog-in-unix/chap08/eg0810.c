/*
 * eg0810.c
 * executing the command-line command using system call 'system'
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../com/comhdr.h"

static void pr_exit( int status );

int main( int argc, char **argv ) {
  int status;
  if ( argc != 2 ) {
    err_quit( "usage: a.out cmd" );
  }
  if ( (status = system( *++argv )) < 0 ) {
    err_sys( "error on system(%s)", *argv );
  }
  pr_exit( status );
  return 0;
}


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
