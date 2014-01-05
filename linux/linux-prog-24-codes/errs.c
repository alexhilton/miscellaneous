/*
 * errs.c -- Using perror and strerror functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

int main( int argc, char **argv )
{
  double d;
  char *p;

  errno = 0;
  d = sqrt( -1 );
  if ( errno ) {
    p = strerror( errno );
    fprintf( stderr, "sqrt(-1):%s\n", p );
  }
  /* reset errno to catch true errors */
  errno = 0;
  d = sqrt( -2 );
  if ( errno ) {
    perror( "sqrt(-2) " );
  }

  exit( EXIT_SUCCESS );
}
