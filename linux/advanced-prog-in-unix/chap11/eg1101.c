/*
 * eg1101.c
 * Show you how to use POSIX library to create thread.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "../com/comhdr.h"

static pthread_t tid;

void print_threadid( const char *msg ) {
  pid_t pid;
  pthread_t thid;

  pid = getpid();
  thid = pthread_self();
  printf( "%s pid is %u, tid is %u, 0x%x\n", msg, 
      (unsigned int) pid, (unsigned int) thid, (unsigned int) thid );
}

void *thread_run( void *arg ) {
  print_threadid( "new thread:" );
  return (void *) 0;
}

int main( int argc, char **argv ) {
  int err;
  if ( (err = pthread_create( &tid, NULL, thread_run, NULL )) != 0 ) {
    err_sys( "error on creating new thread, pthread_create" );
  }

  print_threadid( "master thread(main thread)" );

  sleep( 1 ); /* Let's pray it is long enough */
  return 0;
}
