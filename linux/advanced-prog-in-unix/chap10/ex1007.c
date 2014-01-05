/*
 * ex1007.c
 * Further investigation of function abort().
 * Here we have two version of abort(): one is normal one the other calls
 * _exit() instead of sending signal SIGABRT again, when in case the first
 * sending signal SIGABRT failed.
 * From test result, we know that if first kill(signal) failed, then second one
 * can save the function. If we replace the second kill with _exit(), then the
 * terminatio status will be different completely. But even we use a second
 * kill, who can guarentee that second will succeed all the time? what we can do
 * if it fails, too. Should we add another kill, or use a loop?
 */
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "../com/comhdr.h"

static void abort_normal( void );
static void abort_exit( void );
static void pr_exit( int status );

/*
 * test driver:
 * we will fork two processes then call two version of aborts and parent will
 * print the termination status for them, to see the differences between two
 * versions of abort.
 */
int main( int argc, char **argv ) {
  pid_t pid;
  int status;

  if ( (pid = fork()) < 0 ) {
    err_sys( "fork() error" );
  } else if ( pid == 0 ) {
    printf( "I am child NO1, and I am going by calling abort_normal()\n" );
    abort_normal();
  }
  if ( wait( &status ) != pid ) {
    err_sys( "wait error on processs %d", pid );
  }
  pr_exit( status );

  /* Now second version abort verification */
  if ( (pid = fork()) < 0 ) {
    err_sys( "fork() error" );
  } else if ( pid == 0 ) {
    printf( "I am child NO2, and I am going by calling abort_exit()\n" );
    abort_exit();
  }
  if ( wait( &status ) != pid ) {
    err_sys( "wait error on processs %d", pid );
  }
  pr_exit( status );
  return 0;
}

void abort_normal( void ) {
  sigset_t mask;
  struct sigaction action;

  /* caller can't ignore SIGABRT, if so, reset to default */
  sigaction( SIGABRT, NULL, &action ); /* get current sigaction */
  if ( action.sa_handler == SIG_IGN ) {
    action.sa_handler = SIG_DFL;
    sigaction( SIGABRT, &action, NULL ); /* set the action */
  }
  if ( action.sa_handler == SIG_DFL ) {
    fflush( NULL ); /* flush all open stdio streams */
  }

  /* caller cann't block SIGABRT, make sure it is unblocked */
  sigfillset( &mask );
  sigdelset( &mask, SIGABRT ); /* mask has only SIGABRT turned off */
  /* block all except SIGABRT */
  sigprocmask( SIG_SETMASK, &mask, NULL ); /* no checking for failure */
  kill( getpid(), SIGABRT ); /* send the signal */

  /* If we're here, process caught SIGABRT and returned */
  fflush( NULL );
  action.sa_handler = SIG_DFL;
  sigaction( SIGABRT, &action, NULL ); /* reset to default */

  /* block again and send signal once more, just in case */
  sigprocmask( SIG_SETMASK, &mask, NULL );
  kill( getpid(), SIGABRT );

  exit( 1 ); /* this should never be executed */
}

/*
 * Second version of abort: abort_exit.
 * In the in-case code segment, we will use _exit() instead of sending the
 * signal again
 */
void abort_exit( void ) {
  sigset_t mask;
  struct sigaction action;

  /* caller can't ignore SIGABRT, if so, reset to default */
  sigaction( SIGABRT, NULL, &action ); /* get current sigaction */
  if ( action.sa_handler == SIG_IGN ) {
    action.sa_handler = SIG_DFL;
    sigaction( SIGABRT, &action, NULL ); /* set the action */
  }
  if ( action.sa_handler == SIG_DFL ) {
    fflush( NULL ); /* flush all open stdio streams */
  }

  /* caller cann't block SIGABRT, make sure it is unblocked */
  sigfillset( &mask );
  sigdelset( &mask, SIGABRT ); /* mask has only SIGABRT turned off */
  /* block all except SIGABRT */
  sigprocmask( SIG_SETMASK, &mask, NULL ); /* no checking for failure */
  /*
   * Generally speaking, sending signal SIGABRT once is enough to terminate the
   * process, but if it --- the following line failed, the process is terminated
   * by _exit, which means its termination status will be different from
   * abort().
   * You know, the chance that this kill fails is remote.
   * And, we have reason to doubt about _exit(), and what if it fails, too?
   * Those are remote, anyway
   */
  //kill( getpid(), SIGABRT ); /* send the signal */

  /* If we're here, process caught SIGABRT and returned */
  fflush( NULL );
  _exit( 1 );
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
