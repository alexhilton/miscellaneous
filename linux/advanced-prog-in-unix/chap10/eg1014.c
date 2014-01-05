/*
 * eg1014.c
 * Synchronization between parent process and child process
 * This is analogous to wait()/notify() in Java.
 * One is wait(). Another set some condition and notify().
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../com/comhdr.h"

static volatile sig_atomic_t sigflag; /* set nonzero by signal handler */
static sigset_t newmask, zeromask, oldmask;
/* one signal handler for SIGUSR2, SIGUSR1 */
static void sig_usr( int signo ); 

/*
 * tell_wait()
 * The essential preparations for either parent of child to wait
 * Notice: you have to call this function before calling wait_parent() and
 * wait_child().
 * Another alternative is that we implement this fucntion as a private function
 * of this file and call then in wait_parent and wait_child.
 */
void tell_wait() {
  if ( signal( SIGUSR1, sig_usr ) == SIG_ERR ) {
    err_sys( "signal(SIGUSR1) error" );
  }
  if ( signal( SIGUSR2, sig_usr ) == SIG_ERR ) {
    err_sys( "signal(SIGUSR2) errror" );
  }

  sigemptyset( &zeromask );

  sigemptyset( &newmask );
  sigaddset( &newmask, SIGUSR1 );
  sigaddset( &newmask, SIGUSR2 );

  /* block SIGUSR2 and SIGUSR1, and save current signal mask */
  if ( sigprocmask( SIG_BLOCK, &newmask, &oldmask ) != 0 ) {
    err_sys( "SIG_BLOCK error" );
  }
}


/*
 * tell_parent
 * notify parent we are done
 */
void tell_parent( pid_t pid ) {
  kill( pid, SIGUSR2 );
}

void wait_parent( void ) {
  while ( sigflag == 0 ) {
    sigsuspend( &zeromask );
  }
  sigflag = 0;

  /* restore the signal mask */
  if ( sigprocmask( SIG_SETMASK, &oldmask, NULL ) != 0 ) {
    err_sys( "SIG_SETMASK error" );
  }
}

/* tell child we're done */
void tell_child( pid_t pid ) {
  kill( pid, SIGUSR1 );
}

/*
 * wait_child
 * Wait signal of child -- child notifying us that he is done
 * This (parent) process is suspended, let the child to run, when it finishes it
 * will send us a signal with tell_parent
 */
void wait_child( void ) {
  while ( sigflag == 0 ) {
    sigsuspend( &zeromask );
  }
  sigflag = 0;

  /* restore signal mask */
  if ( sigprocmask( SIG_SETMASK, &oldmask, NULL ) != 0 ) {
    err_sys( "SIG_SETMASK error" );
  }
}

static void sig_usr( int signo ) {
  sigflag  = 1;
}
