/*
 * eg1104.c
 * Show you how to use thread cleanup handlers.
 * There are some issues to note:
 * 	1. use push() and pop() in pairs. We make them in pair but we cannot
 * 	call cleanup handler, so we need to use pop( 0 ) to match each push().
 * 	2. cleanup handler will be called in three circumstances. They are not
 * 	called if you use return in thread.
 * 	3. They are called in reverse order
 */
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "../com/comhdr.h"

void cleanup( void *arg ) {
  printf( "cleanup: %s\n", (char *) arg );
}

void *thread_run( void *arg ) {
  printf( "thread 1 is running\n" );
  pthread_cleanup_push( cleanup, "thread 1, first handler" );
  pthread_cleanup_push( cleanup, "thread 1, second handler" );
  printf( "thread 1 push complete\n" );
  if ( arg != NULL ) {
    return (void *) 1;
  }
  /*
   * You might wonder why we write like this. Because pthread_cleanup_push and
   * pthread_cleanup_pop can be implemented with macros, so we have to use them
   * in pairs, just in case compiler complains. But be cautious, we need to pair
   * each pthread_cleanup_push() with a pthread_cleanup_pop(), but we cannot
   * call the cleanup handler, because we just want to pair the push function.
   * Here comes the pthread_cleanup_pop( 0 ), which does not call cleanup
   * handler.
   */
  pthread_cleanup_pop( 0 );
  pthread_cleanup_pop( 0 );

  return (void *) 1;
}

void *thread2_run( void *arg ) {
  printf( "thread 2 is running\n" );
  pthread_cleanup_push( cleanup, "thread 2 first handler" );
  pthread_cleanup_push( cleanup, "thread 2 second handler" );
  printf( "thread 2 push complete\n" );
  if ( arg != NULL ) {
    pthread_exit( (void *) 2 );
  }
  pthread_cleanup_pop( 0 );
  pthread_cleanup_pop( 0 );
  pthread_exit( (void *) 2 );
}

int main( int argc, char **argv ) {
  int err;
  pthread_t tid, tid2;
  void *ret;

  if ( (err = pthread_create( &tid, NULL, thread_run, (void *) 1 )) != 0 ) {
    err_quit( "cannot create thread 1: %s\n", strerror( err ) );
  }
  if ( (err = pthread_create( &tid2, NULL, thread2_run, (void *) 1 )) != 0 ) {
    err_quit( "cannot create thread 2: %s\n", strerror( err ) );
  }

  if ( (err = pthread_join( tid, &ret )) != 0 ) {
    err_quit( "cannot join thread 1: %s\n", strerror( err ) );
  }
  printf( "exit code of thread 1: %d\n", (int) ret );

  if ( (err = pthread_join( tid2, &ret )) != 0 ) {
    err_quit( "cannot join thread 2: %s\n", strerror( err ) );
  }
  printf( "exit code of thread 2: %d\n", (int) ret );

  return 0;
}
