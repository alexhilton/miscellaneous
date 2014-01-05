/*
 * liftoff.c
 * Emulator rockets lifting off using thread.
 * The counting down before lanuching is by thread.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void *liftoff( void *arg ) {
  int a = *(int *) arg;
  while ( a ) {
    printf( " %d ", a-- );
  }
  printf( "Lift off...\n" );

  return (void *) 0;
}

int main( void ) {
  pthread_t tid;
  for ( int i = 1; i <= 10; i++ ) {
    pthread_create( &tid, NULL, liftoff, (void *) &i );
  }
  printf( "Waiting for lift off:\n" );
  sleep( 10 );
  return 0;
}
