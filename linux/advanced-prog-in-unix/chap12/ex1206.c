/*
 * ex1206.c
 * implement a thread-safe, reliable version of sleep
 * We use recursive lock to make it thread-safe.
 */
 #include <stdio.h>
 #include <pthread.h>
 #include "../com/comhdr.h"
 
 static pthread_mutex_t sleep_lock = PTHREAD_MUTEX_INITIALIZER;
 static pthread_once_t init_done = PTHREAD_ONCE_INIT;
 
 static void sig_alrm( int signo ) {
   /* Nothing to do, just returning wakes up sigsuspend() */
 }
 
 static void init_lock( void ) {
   pthread_mutexattr_t attr;
   pthread_mutexattr_init( &attr );
   pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
   pthead_mutex_init( &sleep_lock, &attr );
   pthread_mutexattr_destroy( &attr );
 }
 
 unsigned int sleep( unsigned int nsecs ) {
   pthread_once( &init_done, init_lock );
   
   struct sigaction newact, oldact;
   sigset_t newmask, oldmask, suspmask;
   unsigned int unslept;
   
   /* set our handler, save previous information */
   newact.sa_handler = sig_alrm;
   sigemptyset( &newact.sa_mask );
   newact.sa_flags = 0;
   sigaction( SIGALRM, &newact, &oldact );
   
   /* Block SIGALRM and save current signal mask */
   sigemptyset( &newmask );
   sigaddset( &newmask, SIGALRM );
   sigprocmask( SIG_BLOCK, &newmask, &oldmask );
   alarm( nsecs );
   
   suspmask = oldmask;
   /* Make sure SIGALRM isn't blocked */
   sigdelset( &suspmask, SIGALRM );
   /* Wait for any signal to be caught */
   sigsuspend( &suspmask );
   
   /*
    * Some signal has been caught and we returned from its handler.
    * Now the signal mask has been reset to one before calling 
    * sigsuspend(), which blocks SIGALRM. So SIGALRM is blocked now.
    */
   unslept = alarm( 0 );
   /* restore previous action */
   sigaction( SIGALRM, &oldact, NULL );
   /* restore previous mask */
   sigprocmask( SIG_SETMASK, &oldmask, NULL );
   pthread_mutex_unlock( &sleep_lock );
   return unslept;
 }