/*
 * eg1109.c
 * Use condition variable to sychronize threads and make them co-operate
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../com/comhdr.h"

struct Message {
  struct Message *next;
  /* More data here */
};

struct Message *work_queue;
pthread_cond_t queue_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;

void process_message( void ) {
  struct Message *mp;

  while ( 1 ) {
    pthread_mutex_lock( &queue_lock );
    while ( work_queue == NULL ) {
      pthread_cond_wait( &queue_ready, &queue_lock );
    }
    mp = work_queue;
    work_queue = mp->next;
    pthread_mutex_unlock( &queue_lock );
    /* now you can process the message */
  }
}

void enqueue_message( struct Message *mp ) {
  pthread_mutex_lock( &queue_lock );
  mp->next  = work_queue;
  pthread_mutex_unlock( &queue_lock );
  /* 
   * You must signal others after releasing the mutex lock, otherwise it will
   * lead to a deadlock
   */
  pthread_cond_signal( &queue_ready );
}
