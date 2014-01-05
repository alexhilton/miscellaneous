/*
 * how to get current time
 */
#include <stdio.h>
#include <time.h>

int main( int argc, char *argv[] ) {
  time_t ctr; /* current time returned by time() */
  time_t cta; /* current time passed into time() */

  ctr = time( &cta );

  printf( "current time is:\n\tctr = %ld\n\tcta = %ld\n", (long) ctr, 
	  (long) cta );
  return 0;
}
