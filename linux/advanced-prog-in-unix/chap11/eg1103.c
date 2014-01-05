/*
 * eg1103.c
 * data sharing problem among threads.
 * Cannot return automatic data in threads to other threads.
 * The data in first thread becomes invalid when parent wants to acces it.
 * Thread, like a function, has its own stack frame, so any automatic variables
 * declared or defined in it becomes invalid once the thread terminates.
 */
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "../com/comhdr.h"

struct Data {
  int a, b, c, d;
};

void print_data( const char *msg, const struct Data *data ) {
  printf( "%s, 0x%x\n", msg, (unsigned int) data );
  printf( "a = %d\nb = %d\nc = %d\nd = %d\n", 
      data->a, data->b, data->c, data->d );
}
void *thread_run( void *arg ) {
  struct Data data = { 1, 2, 3, 4 };

  print_data( "thread 1 running", &data );

  pthread_exit( (void *) &data );
}

void *thread2_run( void *arg ) {
  printf( "thread 2 is running: id is %d\n", pthread_self() );
  pthread_exit( (void *) 0 );
}

int main( int argc, char **argv ) {
  int err;
  pthread_t tid, tid2;
  struct Data *data;

  if ( (err = pthread_create( &tid, NULL, thread_run, NULL )) != 0 ) {
    err_quit( "error on creating first thread: %s\n", strerror( err ) );
  }
  if ( (err = pthread_join( tid, (void *) &data )) != 0 ) {
    err_quit( "error on joining first thread: %S\n", strerror( err ) );
  }
  sleep( 1 ); /* for first thread */
  printf( "main thread starts second thread\n" );
  if ( (err = pthread_create( &tid2, NULL, thread2_run, NULL )) != 0 ) {
    err_quit( "error on creating second thread: %s\n", strerror( err ) );
  }
  sleep( 1 ); /* for second thread */
  print_data( "main thread:", data );

  return 0;
}
