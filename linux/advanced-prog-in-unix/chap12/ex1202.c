/*
 * ex1202.c
 * Implement putenv_r, which is a re-entrant version of putenv.
 * We have made sure that this implementation is async-signal safe
 * as well as thread-safe. The key to thread-safe is use a recursive
 * mutex to lock the environ list when one thread is operating it.
 */
 #include <stdio.h>
 #include <string.h>
 #include <pthread.h>
 #include "../com/comhdr.h"
 
 extern char **environ;
 static pthread_mutex_t env_lock = PTHREAD_MUTEX_INITIALIZER;
 static pthread_once_t init_done = PTHREAD_ONCE_INIT;
 
 static void init_mutex( void ) {
   pthread_mutexattr_t attr;
   pthread_mutexattr_init( &attr );
   pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
   pthread_mutex_init( &env_lock, &attr );
   pthread_mutexattr_destroy( &attr );
 }
 
 extern int putenv_r( char *env_str ) {
   char *env_name = env_str;
   char *env_value = strchr( env_str, '=' );
   if ( env_value == NULL ) {
     /* Not a valid argument */
     return -1;
   }
   /* Make env_name a valid C string */
   *env_value = '\0';
   env_value++;
   pthread_once( &init_done, init_mutex );
   int i;
   int len = strlen( env_name );
   /* Now search the environ list to put env_vlaue into it */
   /* First, we need to acquire the lock */
   pthread_mutex_lock( &env_lock );
   for ( i = 0; environ[ i ] != NULL; i++ ) {
     if ( strncmp( environ[ i ], env_name, len ) == 0
         && environ[ i ][ len ] == '=' ) {
       /* Got a match */
       strcpy( &environ[ i ][ len ], env_value );
       pthread_mutex_unlock( &env_lock );
       return 0;
     }
   }
   pthread_mutex_unlock( &env_lock );
   /* No match found */
   return -1;
 }