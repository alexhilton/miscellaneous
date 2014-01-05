/*
 * eg0808.c
 * a simple implementation of system call 'system'.
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "../com/comhdr.h"

static int system( const char *cmdstr );
static void pr_exit( int status );

int main( int argc, char **argv ) {
  int status;
  if ( (status = system( "date" )) < 0 ) {
    err_sys( "error on system(date)" );
  }
  pr_exit( status );

  if ( (status = system( "nosuchcomd" )) < 0 ) {
    err_sys( "error on system(nosuchcmd)" );
  }
  pr_exit( status );

  if ( (status = system( "who; exit 44" ) ) < 0 ) {
    err_sys( "error on system(who; exit 44)" );
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

static int system( const char *cmdstr ) {
  pid_t pid;
  int status;
  if ( cmdstr == NULL ) {
    return 1; /* always a command processor on Unix */
  }

  if ( (pid = fork() ) < 0 ) {
    err_sys( "error on fork()" );
  } else if ( pid == 0 ) {
    execl( "/bin/sh", "sh", "-c", cmdstr, NULL );
    _exit( 127 ); /* error on execl */
  } else {
    while ( waitpid( pid, &status, 0 ) < 0 ) {
      if ( errno != EINTR ) {
	status = -1; /* error other than EINTER from waitpid() */
      }
    }
  }

  return status;
}
