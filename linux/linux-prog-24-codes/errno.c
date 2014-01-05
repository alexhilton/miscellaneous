/*
 * errno.c -- clearing errno between library calls.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main( int argc, char **argv ) 
{
  double d;
  d = sqrt( ( double ) -1 );
  if ( errno ) {
    perror( "sqrt( - 1 ) failed " );
  /*  errno = 0; */
  } else {
    printf( "sqrt( -1 ) = %f\n", d );
  }

  d = sqrt( ( double ) 2 );
  if ( errno ) {
    perror( "sqrt(2) failed " );
    errno = 0;
  } else {
    printf( "sqrt(2) = %f\n", d );
  }

  exit( EXIT_SUCCESS );
}
