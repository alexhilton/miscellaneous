/*
 * exec.c
 *
 * a program demonstrates how to use exec().
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/* replace this process with the 'ps' command */
static void exec_ps_cmd( void ) {
  static char *argv[] = { "ps", "f", NULL };

  extern char **environ;
  /* exec the 'ps' command: 'ps f' */
  execve( "/bin/ps", argv, environ );

  /* if control reaches here, then the execve() call has failed */
  perror( "execve()" );

}

int main( int argc, char *argv[] ) {
  pid_t pid;
  pid_t wpid;
  int status;

  /* create a new child process */
  pid = fork();

  if ( pid == -1 ) {
    /* fork() failed to create a process */
    perror( "fork()" );
    return 1;
  } else if ( pid == 0 ) {
    /* this is the child process running */
    printf( "PID %ld: child started, parent is %ld\n", 
	    (long) getpid(), (long) getppid() );
    exec_ps_cmd();
  } else {
    /* this is parent process running */
    printf( "PID %ld: started child PID %ld\n",
	    (long) getpid(), (long) pid );
    /* wait for the child process terminats */
    wpid = wait( &status );
    if ( wpid == -1 ) {
      /* wait() failed */
      perror( "wait()" );
      return 1;
    } else if ( wpid != pid ) {
      return 1;
    } else {
      /* the child process has terminated */
      /* do else to check errors */
      if ( WIFEXITED( status ) ) {
	/* normal exit */
	printf( "exited: $? = %d\n", WEXITSTATUS( status ) );
      } else if ( WIFSIGNALED( status ) ) {
	/* process abort, kill or signal */
	printf( "signal: %d%s\n", WTERMSIG( status ),
		(WCOREDUMP(status) ? " with core file." : "") );
      } else {
	/* stopped child process */
	printf( "stopped\n" );
      }
    }
  }

  return 0;
}
