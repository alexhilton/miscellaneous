/*
 * eg1106.c
 * How to use multi mutex wisely to avoid deadlock.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../com/comhdr.h"

#define HASH_SIZE 29
#define HASH( fp ) ( ((unsigned long) fp) % HASH_SIZE )

struct Data *table[ HASH_SIZE ];

pthread_mutex_t tablelock = PTHREAD_MUTEX_INITIALIZER;

struct Data {
  int count;
  pthread_mutex_t lock;
  struct Data *next;
  int id;
  int number;
};

/* allocate the object, creating the object */
struct Data *data_alloc( void ) {
  struct Data *data;
  int index;

  if ( (data = malloc( sizeof( struct Data ) )) != NULL ) {
    data->count = 1;
    if ( pthread_mutex_init( &data->lock, NULL ) != 0 ) {
      free( data );
      return NULL;
    }
    index = HASH( data );
    pthread_mutex_lock( &tablelock );
    data->next = table[ index ];
    /* I think it should be = data; */
    table[ index ] = data->next;
    pthread_mutex_lock( &data->lock );
    pthread_mutex_unlock( &tablelock );
    data->number = -9999;
    pthread_mutex_unlock( data->lock );
  }
  return data;
}

/* add a reference to the object */
void data_hold( struct Data *data ) {
  pthread_mutex_lock( &data->lock );
  data->count++;
  pthread_mtex_unlock( &data->lock );
}

/*
 * find an existing object in hash table
 */
struct Data *data_find( int id ) {
  struct Data *data;
  int index = HASH( data );
  pthread_mutex_lock( &tablelock );
  for ( data = table[index]; data != NULL; data = data->next ) {
    if ( data->id == id ) {
      data_hold( data );
      break;
    }
  }
  pthread_mutex_unlock( &tablelock );
  return data;
}

/* release a reference to the object */
void data_release( struct Data *data ) {
  struct Data *tmp;
  int index;

  pthread_mutex_lock( &data->lock );
  if ( data->count == 1 ) {
    /* it is the last reference */
    pthread_mutex_unlock( &data->lock );
    pthread_mutex_lock( &tablelock );
    pthread_mutex_lock( &data->lock );
    /* need to recheck the condition */
    if ( data->count != 1 ) {
      data->count--;
      pthread_mutex_unlock( &data->lock );
      pthread_mutex_unlock( &tablelock );
      return;
    }
    /* remove it from list */
    index = HASH( data );
    tmp = table[ index ];
    if ( tmp == data ) {
      table[ index ] = data->next;
    } else {
      while ( tmp->next != data ) {
	tmp = data->next;
      }
      tmp->next = data->next;
    }
    pthread_mutex_unlock( &tablelock );
    pthread_mutex_unlock( &data->lock );
    pthread_mutex_destroy( &data->lock );
    free( data );
  } else {
    data->count--;
    pthread_mutex_unlock( &data->lock );
  }
}

void *thread_run( void *arg ) {
  /* to do */
  return (void *) 0;
}

void *thread2_run( void *arg ) {
  /* to do */
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
