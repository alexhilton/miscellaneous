/*
 * eg1105.c
 * Show you how to use Mutex -- mutual exclusion to sychronize multi threads.
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../com/comhdr.h"

struct Data {
  int count; /* reference count, when it reaches 0, we can destroy the object */
  pthread_mutex_t lock; /* the lock to protect this object */
  int number; /* object's data */
};

static struct Data *data = NULL;
/*
 * create a new data object
 * Here we don't have to lock the object, since we are only one referencing it
 */
struct Data *data_alloc( void ) { 
  struct Data *data;
  if ( (data = malloc( sizeof( struct Data ) )) != NULL ) {
    data->count = 1;
    if ( pthread_mutex_init( &data->lock, NULL ) != 0 ) {
      free( data );
      return NULL;
    }
    data->number = -9999;
  }

  return data;
}

void data_hold( struct Data *data ) {
  assert( data != NULL );
  pthread_mutex_lock( &data->lock );
  data->count++;
  pthread_mutex_unlock( &data->lock );
}

/* release a reference to the object */
void data_release( struct Data *data ) {
  assert( data != NULL );
  pthread_mutex_lock( &data->lock );
  if ( --data->count == 0 ) {
    /* It is the last reference */
    pthread_mutex_unlock( &data->lock );
    pthread_mutex_destroy( &data->lock );
    free( data );
  } else {
    pthread_mutex_unlock( &data->lock );
  }
}

/* executing task for first thread */
void *thread_run( void *arg ) {
  if ( data == NULL ) {
    if ( (data = data_alloc()) == NULL ) {
      return (void *) (-1);
    }
  }
  data_hold( data );
  data->number = 1111;
  printf( "data->number is %d\n", data->number );
  data_release( data );
  return (void *) 0;
}

/* executing task for second thread */
void *thread2_run( void *arg ) {
  if ( data == NULL ) {
    if ( (data = data_alloc()) == NULL ) {
      return (void *) (-1);
    }
  }
  data_hold( data );
  data->number = 2222;
  printf( "data->number is %d\n", data->number );
  data_release( data );
  return (void *) 0;
}

/* test driver */
int main( int argc, char **argv ) {
  pthread_t tid, tid2;
  int err;

  if ( (err = pthread_create( &tid, NULL, thread_run, NULL )) != 0 ) {
    err_quit( "error on creating first thread: %s\n", strerror( err ) );
  }
  if ( (err = pthread_create( &tid2, NULL, thread2_run, NULL )) != 0 ) {
    err_quit( "error on creating second thread: %s\n", strerror( err ) );
  }

  return 0;
}
