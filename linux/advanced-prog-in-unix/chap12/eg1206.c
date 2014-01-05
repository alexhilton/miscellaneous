/*
 * eg1206.c
 * Thread and signal
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include "../com/comhdr.h"

/* set non-zero by thread */
static int quit_flag;
static sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait = PTHREAD_COND_INITIALIZER;

void *thread_run( void *arg ) {
  int err, signo;
  while ( 1 ) {
    err = sigwait( &mask, &signo );
    if ( err != 0 ) {
      err_exit( err, "sigwait failed" );
    }
    switch ( signo ) {
    case SIGINT:
      printf( "\nInterrupt\n" );
      break;
    case SIGQUIT:
      pthread_mutex_lock( &lock );
      quit_flag = 1;
      pthread_mutex_unlock( &lock );
      pthread_cond_signal( &wait );
      return 0;
    default:
      printf( "unexpected signal %d\n", signo );
      exit( EXIT_FAILURE );
    }
  }
}

int main( void ) {
  int err;
  sigset_t old_mask;
  pthread_t tid;

  sigemptyset( &mask );
  sigaddset( &mask, SIGINT );
  sigaddset( &mask, SIGQUIT );
  if ( (err = pthread_sigmask( SIG_BLOCK, &mask, &old_mask )) != 0 ) {
    err_exit( err, "SIG_BLOCK error" );
  }
  err = pthread_create( &tid, NULL, thread_run, 0 );
  if ( err != 0 ) {
    err_exit( err, "cannot create thread" );
  }

  /* To protect condition 'wait' */
  pthread_mutex_lock( &lock );
  while ( quit_flag == 0 ) {
    pthread_cond_wait( &wait, &lock );
  }
  pthread_mutex_unlock( &lock );

  /* SIGQUIT has been caught and is now blocked, do whatever */
  quit_flag = 0;

  /* reset signal mask which unblocks SIGQUIT */
  if ( sigprocmask( SIG_SETMASK, &old_mask, NULL ) < 0 ) {
    err_sys( "SIG_SETMASK failed" );
  }

  return 0;
}
