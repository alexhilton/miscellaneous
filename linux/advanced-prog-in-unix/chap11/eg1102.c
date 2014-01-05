/*
 * eg1102.c
 * Show you how to terminate a thread, and fetch its termination status.
 */
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include "../com/comhdr.h"

void *thread_run( void *arg ) {
  printf( "thread 1 is running\n" );
  return (void *) 1;
}

void *thread2_run( void *arg ) {
  printf( "thread 2 is running\n" );
  pthread_exit( (void *) 2 );
}

int main( int argc, char **argv ) {
  int err;
  pthread_t tid, tid2;
  /* Why, ret is a pointer to typeless, then how comes (int) ret */
  void *ret;

  /* create and run first thread */
  if ( (err = pthread_create( &tid, NULL, thread_run, NULL )) != 0 ) {
    err_quit( "error on creating first thread: %s\n", strerror( err ) );
  }
  if ( (err = pthread_create( &tid2, NULL, thread2_run, NULL )) != 0 ) {
    err_quit( "error on creating second thread: %s\n", strerror( err ) );
  }
  if ( (err = pthread_join( tid, &ret )) != 0 ) {
    err_quit( "error on joining first thread: %s\n", strerror( err ) );
  }
  printf( "exit code of thread 1 is: %d\n", (int) ret );

  if ( (err = pthread_join( tid2, &ret )) != 0 ) {
    err_quit( "error on joining second thread: %s\n", strerror( err ) );
  }
  printf( "exit code of thread 2 is: %d\n", (int) ret );

  return 0;
}
