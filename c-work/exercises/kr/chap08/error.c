/**
 * error.c
 * implementation of error.h
 * a function to report errors along with other infos.
 */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/* print an error message and die */
extern void error( char *fmt, ... ) {
  va_list args;

  va_start( args, fmt );
  fprintf( stderr, "Error: " );
  vfprintf( stderr, fmt, args );
  fprintf( stderr, "\n" );
  va_end( args );
  exit( EXIT_FAILURE );
}
