/*
 * cond.c
 * use a condition variable to wait for mama's supper.
 */
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t meal_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t meal_ready = PTHREAD_COND_INITIALIZER;
static char *meal = NULL;

/* The consumer */
static void *thread1_run( void *arg ) {
  pthread_mutex_lock( &meal_lock );
  while ( meal == NULL ) {
    pthread_cond_wait( &meal_ready, &meal_lock );
  }
  printf( "I can eat: %s\n", meal );
  meal = NULL;
  pthread_mutex_unlock( &meal_lock );

  return (void *) 0;
}

static void *thread2_run( void *arg ) {
  meal = "Turkey";
  printf( "meal is ready\n" );
  pthread_cond_signal( &meal_ready );

  return (void *) 0;
}

int main( void ) {
  pthread_t tid, tid2;
  pthread_create( &tid, NULL, thread1_run, NULL );
  pthread_create( &tid2, NULL, thread2_run, NULL );
  return 0;
}
