/*
 * philosopher.c
 * Classic Dining philosopher problem demonstrating how to create deadlock---how
 * deadlock comes out.
 * We will use some tricks to eliminate the deadlock in fixed_ph.c.
 */
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int taken;
  pthread_mutex_t lock;
  pthread_cond_t ready;
} Chopstick;

static Chopstick chop_new() {
  Chopstick chop;
  chop.taken = 0;
  pthread_mutex_init( &chop.lock, NULL );
  pthread_cond_init( &chop.ready, NULL );
  return chop;
}

static void chop_take( Chopstick chop ) {
  pthread_mutex_lock( &chop.lock );
  while ( chop.taken ) {
    pthread_cond_wait( &chop.ready, &chop.lock );
  }
  chop.taken = 1;
  pthread_mutex_unlock( &chop.lock );
}

static void chop_drop( Chopstick chop ) {
  pthread_mutex_lock( &chop.lock );
  chop.taken = 0;
  pthread_mutex_unlock( &chop.lock );
  pthread_cond_signal( &chop.ready );
}

typedef struct {
  Chopstick left;
  Chopstick right;
  int id;
} Philosopher;

static Philosopher ph_new( int id, Chopstick left, Chopstick right ) {
  Philosopher ph;
  ph.id = id;
  ph.left = left;
  ph.right = right;
  return ph;
}

static void thinking() {
  int s = rand() % 1133;
  usleep( s );
}

static void *ph_dining( void *p ) {
  Philosopher *ph = (Philosopher *) p;
  printf( "Philosopher #%02d is thinking\n", ph->id );
  thinking();
  printf( "Philosopher #%02d is grabbing left\n", ph->id );
  chop_take( ph->left );
  printf( "Philosopher #%02d is grabbing right\n", ph->id );
  chop_take( ph->right );
  printf( "Philosopher #%02d is eating\n", ph->id );
  thinking();
  chop_drop( ph->left );
  chop_drop( ph->right );
  return (void *) 0;
}

int main( void ) {
  Chopstick chops[ 5 ];
  int size = 5;
  int i;
  int id = 0;
  for ( i = 0; i < size; i++ ) {
    chops[ i ] = chop_new();
  }

  Philosopher phs[ 5 ];
  for ( i = 0; i < size; i++ ) {
    phs[ i ] = ph_new( ++id, chops[ i ], chops[ (i+1) % size ] );
  }
  pthread_t pid[ 5 ];
  for ( i = 0; i < size; i++ ) {
    pthread_create( &pid[ i ], NULL, ph_dining, (void *) &phs[ i ] );
  }
  printf( "Print 'Enter' to quit:" );
  getchar();
  return 0;
}
