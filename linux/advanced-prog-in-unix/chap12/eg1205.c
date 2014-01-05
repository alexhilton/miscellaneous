/*
 * eg1205.c
 * Another thread-safe version of getenv.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
static pthread_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thread_init( void ) {
  /* pointed by 'key', destructed by 'free' */
  pthread_key_create( &key, free );
}

/*
 * We store the query result in a thread specific buffer which means each thread
 * gets its own buffer, not interferencing with others.
 */
char *getenv( const char *env_name ) {
  int i, len;
  char *env_value;

  pthread_once( &init_done, thread_init );
  pthread_mutex_lock( &env_mutex );
  env_value = (char *) pthread_getspecific( key );
  if ( env_value == NULL ) {
    /* Has not got specific data, we create it one */
    env_value = (char *) malloc( ARG_MAX );
    if ( env_value == NULL ) {
      /* Out of memory, nothing to do */
      pthread_mutex_unlock( &env_mutex );
      return NULL;
    }
    /* Make env_value in which query result is stored thread specific */
    pthread_setspecific( key, env_value );
  }
  len = strlen( env_name );
  for ( i = 0; environ[i] != NULL; i++ ) {
    if ( (strncmp( env_name, environ[i], len ) == 0)
	&& (environ[i][len] == '=') ) {
      /* Got a match */
      strcpy( env_value, &environ[ i ][ len+1 ] );
      pthread_mutex_unlock( &env_mutex );
      return env_value;
    }
  }
  /* Not match found */
  pthread_mutex_unlock( &env_mutex );
  return NULL;
}
