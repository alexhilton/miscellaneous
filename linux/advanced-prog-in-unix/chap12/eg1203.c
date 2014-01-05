/*
 * eg1203.c
 * A non-reentrant version of getenv, which is not thread-safe
 * If there are two threads, for instance, want to retrieve
 * the environment variable. The chances are that first thread was blocked
 * before getenv returned and the second thread was switched to run. When first
 * thread woke up and returned from getenv, it got just result of second
 * thread's query. Because envbuf in which returned value was stored is a static
 * global variable, so first thread's result might be overwritten by second
 * thread.
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include "../com/comhdr.h"

static char envbuf[ ARG_MAX ];

extern char **environ;

char *getenv( const char *env_name ) {
  int i, len;
  len = strlen( env_name );
  for ( i = 0; environ[i] != NULL; i++ ) {
    if ( (strncmp( env_name, environ[i], len ) == 0)
	&& (environ[i][len] == '=') ) {
      strcpy( envbuf, &environ[ i ][ len + 1 ] );
      return envbuf;
    }
  }
  return NULL;
}


/* Test driver */
int main( void ) {
  return 0;
}
