/*
 * eg1201.c
 * Create a thread in a detached state
 */
#include <stdio.h>
#include <pthread.h>
#include "../com/comhdr.h"

/* Creating a thread in a detached state */
int make_thread( void *(*fn)(void *), void *arg ) {
  int err;
  pthread_t tid;
  pthread_attr_t attr;

  err = pthread_attr_init( &attr );
  if ( err != 0 ) {
    return err;
  }
  err = pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
  if ( err == 0 ) {
    err = pthread_create( &tid, &attr, fn, arg );
  }
  pthread_attr_destroy( &attr );
  return err;
}
