/*
 * eg1204.c
 * A thread-safe version of getenv.
 * We use a lock --- recursive mutex and storing result in caller's buffer to
 * resolve the race condition.
 */
#include <errno.h>
#include <pthread.h>

extern char **environ;

static pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init( void ) {
  pthread_mutexattr_t attr;
  pthread_mutexattr_init( &attr );
  pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
  pthread_mutex_init( &env_mutex, &attr );
  pthread_mutexattr_destroy( &attr );
}

/*
 * Storing querying result in caller's buffer will solve the race condition,
 * Which makes it impossible for one thread to overwrite another thread's
 * result.
 */
int getenv_r( const char *env_name, char *env_value, int env_value_len_limit ) {
  int i, len, old_len;

  /* To ensure that it is initialized only once */
  pthread_once( &init_done, thread_init );
  len = strlen( env_name );
  pthread_mutex_lock( &env_mutex );
  for ( i = 0; environ[i] != NULL; i++ ) {
    if ( (strncmp( env_name, environ[i], len ) == 0)
	&& (environ[i][len] == '=') ) {
      old_len = strlen( &environ[ i ][ len+1 ] );
      if ( old_len >= buflen ) {
	/* Buffer overflowing, report error */
	pthread_mutex_unlock( &env_mutex );
	return ENOSPC;
      }
      strcpy( env_value, &environ[ i ][ len+1 ] );
      pthread_mutex_unlock( &env_mutex );
      return 0;
    }
  }
  /* Up to here, no match found, report an error */
  pthread_mutex_unlock( &env_mutex );
  return ENOENT;
}

/* Test driver */
int main( void ) {
  return 0;
}
