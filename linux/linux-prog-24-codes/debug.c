/*
 * desing a debug system to trace subroutine and print some
 * debugging message.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* 
 * Trace by TRACE_LEVEL & TRACE_SUBSYS macro:
 */
#define TRACE_SUBSYSF( level, subsys, msg ) { \
  if ( testSubsystem( level, subsys ) ) { \
    printf( "%s @ %u : ", __FILE__, __LINE__ ); \
    printf msg; \
    fflush( stdout ); \
  } \
}

/*
 * set environment variable for this session.
 */
void init() {
  putenv( "TRACE_LEVE=5" );
}

/*
 * Support function for TRACE_SUBSYSF() macro;
 * 
 * Environment variables:
 *  TRACE_LEVEL=n             Sets debug level
 *  TRACE_SUBSYS=sys1, sys2   Defines which subsystems will be traced
 *  
 * If TRACE_LEVEL is defined, but TRACE_SUBSYS is not, then all subsystems
 * will be traced at the appropriate level.
 */

static int
testSubsystem( short level, const char *subsys ) {
  char *cp;
  char vbuf[ 128 ];       /* buffer for variable */
  static short trace_level = -1; /* Trace level after init */
  static char *trace_subsys = 0; /* Pointer to environment val */

  /*
   * One time initialization: Test for the presence of the
   * environment variables TRACE_LEVEL and TRACE_SUBSYS.
   */
  if ( trace_level == -1 ) {
    trace_subsys = getenv( "TRACE_SUBSYS" ); /* get variable */
    if ( (cp = getenv( "TRACE_LEVEL" )) != NULL ) {
      trace_level = atoi( cp );
    } else {
      trace_level = 0;
    }
  }

  /*
   * If the TRACE_LEVEL is lower than this macro call, then return false.
   */
  if ( trace_level < level ) { /* tracing at lower level */
    return 0;
  }

  /*
   * Return true if no TRACE_SUBSYS environment value is defined.
   */
  if ( !trace_subsys ) {
    return 1;
  }

  /*
   * Copy string so we don't modify ENV variable.
   */
  strncpy( vbuf, trace_subsys, sizeof( vbuf ) );
  vbuf[ sizeof( vbuf ) - 1 ] = '\0';

  /*
   * Scan if we have a matching subsystem token;
   */
  for ( cp=strtok(vbuf, ","); cp!=NULL; cp=strtok(NULL, ",") ) {
    if ( !strcmp( subsys, cp ) ) {
      return 1;
    }
  }
  return 0;
}

/* main program */
int main( int argc, char *argv[] ) {
  init();
  TRACE_SUBSYSF( 5, "SYSA", ("argv[0]='%s'\n", argv[0]) );
  printf( "Program debug.c\n" );
  TRACE_SUBSYSF( 3, "SYSB", ("argc=%d\n", argc) );

  return 0;
}
