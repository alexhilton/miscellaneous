/*
 * toast.c
 * Testing the blockingqueue.
 * Each piece of toast has four periods --- creating, buttering, jamming and
 * eating. They must happen in that order. We use four threads to do creating,
 * buttering, jamming and eating. And we use BlockingQueue to synchronize
 * them.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "blockingqueue.h"

static pthread_mutex_t done_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t done_cond = PTHREAD_COND_INITIALIZER;
static int done = 0;

enum { DRY, BUTTERED, JAMMED };

typedef struct Toast {
  int id;
  int status;
} Toast;

typedef struct TQueue {
  BlockingQueue from;
  BlockingQueue to;
} TwoQueue;

static int id = 0;
static void *toaster( void *queue ) {
  /*
   * You cannot return a local variable or add local variable into an global
   * data structure. Thread has its own stack frame, every local variable
   * becomes invalid when thread exits.
   * The solution is use dynamical alocation or declare them globally
   */
  Toast *toast = (Toast *) malloc( sizeof( *toast ) );
  toast->id = ++id;
  toast->status = DRY;
  printf( "Toast #%02d: dry\n", toast->id );
  blockingqueue_enqueue( (BlockingQueue) queue, (void *) toast );
  return (void *) 0;
}

static void *butterer( void *queue ) {
  TwoQueue *qs = (TwoQueue *) queue;
  Toast *t = (Toast *) blockingqueue_dequeue( qs->from );
  assert( t != NULL );
  t->status = BUTTERED;
  printf( "Toast #%02d: buttered\n", t->id );
  blockingqueue_enqueue( qs->to, (void *) t );
  return (void *) 0;
}

static void *jammer( void *queue ) {
  TwoQueue *qs = (TwoQueue *) queue;
  Toast *t  = (Toast *) blockingqueue_dequeue( qs->from );
  assert( t != NULL );
  t->status = JAMMED;
  printf( "Toast #%02d: Jammed\n", t->id );
  blockingqueue_enqueue( qs->to, (void *) t );
  return (void *) 0;
}

static void *eater( void *queue ) {
  Toast *t = (Toast *) blockingqueue_dequeue( (BlockingQueue) queue );
  assert( t != NULL );
  printf( "enjoying toast #%02d\n", t->id );
  /* Make sure you change the condition before signaling */
  done = 1;
  pthread_cond_signal( &done_cond );
  return (void *) 0;
}

int main( void ) {
  BlockingQueue dry_queue = blockingqueue_new();
  BlockingQueue buttered_queue = blockingqueue_new();
  BlockingQueue finished_queue = blockingqueue_new();
  TwoQueue to_butterer, to_jammer;
  to_butterer.from = dry_queue;
  to_butterer.to = buttered_queue;
  to_jammer.from = buttered_queue;
  to_jammer.to = finished_queue;

  pthread_t t, b, e, j;
  pthread_create( &e, NULL, eater, (void *) finished_queue );
  pthread_create( &j, NULL, jammer, (void *) &to_jammer );
  pthread_create( &b, NULL, butterer, (void *) &to_butterer );
  pthread_create( &t, NULL, toaster, (void *) dry_queue );
  /*
   * From now on, the main thread must sleep long enough for sub-threads to
   * finishing their jobs, otherwise the program will exit.
   */
  pthread_mutex_lock( &done_lock );
  while ( !done ) {
    pthread_cond_wait( &done_cond, &done_lock );
  }
  pthread_mutex_unlock( &done_lock );
  blockingqueue_destroy( dry_queue );
  blockingqueue_destroy( buttered_queue );
  blockingqueue_destroy( finished_queue );
  return 0;
}
