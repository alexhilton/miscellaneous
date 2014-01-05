/*
 * mutexlock.c
 * Use a mutexlock to protect the fund
 */
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t fund_lock = PTHREAD_MUTEX_INITIALIZER;
static int fund;

static void *thread1_run( void * arg ) {
  printf( "Before thread1 adding: %d\n", fund );
  pthread_mutex_lock( &fund_lock );
  fund += 200;
  pthread_mutex_unlock( &fund_lock );
  printf( "thread1 add 200: %d\n", fund );

  return (void *) 0;
}

static void *thread2_run( void *arg ) {
  printf( "Before thread2 adding: %d\n", fund );
  pthread_mutex_lock( &fund_lock );
  fund += 200;
  pthread_mutex_unlock( &fund_lock );
  printf( "thread2 add 200: %d\n", fund );

  return (void *) 0;
}

int main( void ) {
  pthread_t id1, id2;
  pthread_create( &id1, NULL, thread1_run, NULL );
  pthread_create( &id2, NULL, thread2_run, NULL );

  return 0;
}
