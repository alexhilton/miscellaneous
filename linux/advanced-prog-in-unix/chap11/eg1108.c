/*
 * eg1108.c
 * #(@) Alex Hilton
 * Dec 31 2009
 * (c) Copyright Alex Hilton all rights reserved
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../com/comhdr.h"

/**
 * eg1108.c
 * Use a readerwriter lock to protect a job queue
 */

struct Job {
  struct Job *next;
  struct Job *prev;
  /* Tells which thread handles this job */
  pthread_t id;
};

struct Queue {
  struct Job *head;
  struct Job *tail;
  pthread_rwlock_t lock;
};

/* Create and initialize a new queue */
int queue_init( struct Queue *qp ) {
  int err;
  qp->head = NULL;
  qp->tail = NULL;
  err = pthread_rwlock_init( &qp->lock, NULL );
  if ( err != 0 ) {
    return err;
  }
  /* Continue to initialize other fields in the queue */
  return 0;
}

/* Insert a Job at the head of the queue */
void job_insert( struct Queue *qp, struct Job *jp ) {
  pthread_rwlock_wrlock( &qp->lock );
  jp->next = qp->head;
  jp->prev = NULL;
  if ( qp->head != NULL ) {
    qp->head->prev = jp;
  } else {
    qp->tail = jp;
  }
  qp->head = jp;
  pthread_rwlock_unlock( &qp->lock );
}

/* Append a job on the tail of the queue */
void job_append( struct Queue *qp, struct Job *jp ) {
  pthread_rwlock_wrlock( &qp->lock );
  jp->next = NULL;
  jp->prev = qp->tail;
  if ( qp->tail != NULL ) {
    qp->tail->next = jp;
  } else {
    qp->head = jp;
  }
  qp->tail = jp;
  pthread_rwlock_unlock( &qp->lock );
}

/* Remove the given job from the queue */
void job_remove( struct Queue *qp, struct Job *jp ) {
  pthread_rwlock_rwlock( &qp->lock );
  if ( jp == qp->head ) {
    qp->head = jp->next;
    if ( qp->tail == jp ) {
      qp->tail = NULL;
    }
  } else if ( jp == qp->tail ) {
    qp->tail = jp->prev;
    if ( qp->head == jp ) {
      qp->head = NULL;
    }
  } else {
    jp->prev->next = jp->next;
    jp->next->prev = jp->prev;
  }
  pthread_rwlock_unlock( &qp->lock );
}

/* Find a job for given thread id */
struct Job *job_find( struct Queue *qp, pthread_t id ) {
  struct Job *jp;
  if ( pthread_rwlock_rdlock( &qp->lock ) != 0 ) {
    return NULL;
  }
  for ( jp = qp->head; jp != NULL; jp = jp->next ) {
    if ( pthread_equal( jp->id, id ) ) {
      break;
    }
  }

  pthread_rwlock_unlock( &qp->lock );
  return jp;
}
