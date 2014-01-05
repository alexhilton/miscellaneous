/*
 * eg1202.c
 * Using recursive mutex
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "../com/comhdr.h"

extern int make_thread( void *(*)(void *), void * );

struct Info {
  void (*func)( void * ); /* function to call */
  void *arg; /* arguments for function above */
  struct timespec time2wait;
};

/* seconds to nanoseconds */
#define SEC_TO_NSEC 1000000000
/* microseconds to nanoseconds */
#define USE_TO_NSEC 1000

/* Call the function in arg when arg->time2wait expires */
void *timeout_helper( void *arg ) {
  struct Info *tip;

  tip = (struct Info *) arg;
  nanosleep( &tip->time2wait, NULL );
  (*tip->func)(tip->arg);

  return (void *)0; /* NULL */
}

void timeout( const struct timespec *when, void (*func)(void *),
    void *arg ) {
  struct timespec now;
  struct timeval tv;
  struct Info *tip;

  gettimeofday( &tv, NULL );
  now.tv_sec = tv.tv_sec;
  now.tv_nsec = tv.tv_usec * USE_TO_NSEC;

  /* 
   * We will wait until timeout to execute function, 
   * if 'when' is in the future
   */
  if ( (when->tv_sec > now.tv_sec) 
      || ((when->tv_sec == now.tv_sec) && (when->tv_nsec > now.tv_nsec)) ) {
    tip = (struct Info *) malloc( sizeof( struct Info ) );
    if ( tip != NULL ) {
      tip->func = func;
      tip->arg = arg;
      /* Calculate how much time left to 'when' */
      tip->time2wait.tv_sec = when->tv_sec - now.tv_sec;
      if ( when->tv_nsec >= now.tv_nsec ) {
	tip->time2wait.tv_nsec = when->tv_nsec - now.tv_nsec;
      } else {
	tip->time2wait.tv_sec--;
	tip->time2wait.tv_nsec = SEC_TO_NSEC - now.tv_nsec + when->tv_nsec;
      }
      if ( make_thread( timeout_helper, (void *) tip ) == 0 ) {
	return;
      }
    }
  }

  /*
   * We get here if (a) when <= now, or (b) malloc fails,
   * or (c) we can't make a thread, so we just call the function now.
   */
  (*func)( arg );
}

static pthread_mutexattr_t attr;
static pthread_mutex_t mutex;

void retry( void *arg ) {
  pthread_mutex_lock( &mutex );
  /* Perform retry steps ... */
  pthread_mutex_unlock( &mutex );
}

int main( void ) {
  int err, condition, arg;
  struct timespec when;
  if ( (err = pthread_mutexattr_init( &attr )) != 0 ) {
    err_exit( err, "pthread_mutexattr_init failed" );
  }
  if ( (err = pthread_mutexattr_settype( 
	  &attr, PTHREAD_MUTEX_RECURSIVE )) != 0 ) {
    err_exit( err, "cannot set recursive type" );
  }
  if ( (err = pthread_mutex_init( &mutex, &attr )) != 0 ) {
    err_exit( err, "cannot create recursive mutex" );
  }

  pthread_mutex_lock( &mutex );
  if ( condition ) {
    /* calculate target time 'when' */
    timeout( &when, retry, (void *) arg );
  }
  pthread_mutex_unlock( &mutex );

  return 0;
}

/* Creating a thread in a detached state */
extern int make_thread( void *(*fn)(void *), void *arg ) {
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
