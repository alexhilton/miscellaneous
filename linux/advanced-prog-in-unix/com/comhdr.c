/**
 * comhdr.c
 * implementation of comhdr.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include "comhdr.h"

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag"
 */
static void err_doit( int ef, int en, const char *fmt, va_list ap );

/* 
 * Non fatal error related to a system call
 * Print a message and return.
 */
void err_ret( const char *fmt, ... ) {
  va_list ap;
  va_start( ap, fmt );
  err_doit( 1, errno, fmt, ap );
  va_end( ap );
}

/*
 * Fatal error related to a system call
 * Print a message and terminates
 */
void err_sys( const char *fmt, ... ) {
  va_list ap;
  va_start( ap, fmt );
  err_doit( 1, errno, fmt, ap );
  va_end( ap );
  exit( EXIT_FAILURE );
}

/*
 * Fatal error  unrelated to a system call.
 * Error code passed as explict parameter. Print a message
 * and terminate.
 */
void err_exit( int error, const char *fmt, ... ) {
  va_list ap;
  va_start( ap, fmt );
  err_doit( 1, error, fmt, ap );
  va_end( ap );

  exit( 1 );
}

/*
 * Fatal error related to a system call
 * Print a message, dump core, and terminates
 */
void err_dump( const char *fmt, ... ) {
  va_list ap;
  va_start( ap, fmt );
  err_doit( 1, errno, fmt, ap );
  va_end( ap );
  abort(); /* dump core and terminate */
  exit( EXIT_FAILURE );
}

/*
 * Nonfatal error unrelated to a system call
 * Print a message and return
 */
void err_msg( const char *fmt, ... ) {
  va_list ap;
  va_start( ap, fmt );
  err_doit( 0, 0, fmt, ap );
  va_end( ap );
  return;
}

/*
 * Fatal error unrelated to a system call
 * Print a message and terminate.
 */
void err_quit( const char *fmt, ... ) {
  va_list ap;
  va_start( ap, fmt );
  err_doit( 0, 0, fmt, ap );
  va_end( ap );
  exit( EXIT_FAILURE );
}

/*
 * Print a message and return to caller
 * Caller specifies "errnoflag"
 */
static void err_doit( int ef, int en, const char *fmt, va_list ap ) {
  char buf[ MAXLINE ];

  vsnprintf( buf, MAXLINE, fmt, ap );
  if ( ef ) {
    snprintf( buf+strlen(buf), MAXLINE-strlen(buf), ": %s",
	strerror( en ) );
  }
  strcat( buf, "\n" );
  fflush( stdout ); /* in case stdout and stderr are the same */
  fputs( buf, stderr );
  fflush( NULL ); /* flushes all stdio output streams */
}
