/*
 * eg1207.c
 * thread and fork, the legacy problem when forking a new process
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "../com/comhdr.h"

static pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

/* Handler just before forking */
void prepare( void ) {
  printf( "preparing locks...\n" );
  pthread_mutex_lock( &lock1 );
  pthread_mutex_lock( &lock2 );
}

/* Parent's handler before fork returns */
void parent( void ) {
  printf( "parent unlocking locks...\n" );
  pthread_mutex_unlock( &lock1 );
  pthread_mutex_unlock( &lock2 );
}

/* Child's handler before fork returns */
void child( void ) {
  printf( "child unlocking locks...\n" );
  pthread_mutex_unlock( &lock1 );
  pthread_mutex_unlock( &lock2 );
}

void *thread_run( void *arg ) {
  printf( "thread started...\n" );
  pause();
  return (void *) 0;
}

int main( void ) {
  int err;
  pid_t pid;
  pthread_t tid;

#if defined( BSD ) || defined( MACOS )
  printf( "pthread atfork is unsupported\n" );
#else
  if ( (err = pthread_atfork( prepare, parent, child )) != 0 ) {
    err_exit( err, "cannot install fork handlers" );
  }
  err = pthread_create( &tid, NULL, thread_run, 0 );
  if ( err != 0 ) {
    err_exit( err, "cannot create thread" );
  }
  sleep( 2 ); /* TODO: why ? */
  printf( "parent about to fork...\n" );
  if ( (pid = fork()) < 0 ) {
    err_quit( "fork failed" );
  } else if ( pid == 0 ) {
    /* child is running */
    printf( "child returned from fork\n" );
  } else {
    /* parent is running */
    printf( "parent returned from fork\n" );
  }
#endif
  return 0;
}
