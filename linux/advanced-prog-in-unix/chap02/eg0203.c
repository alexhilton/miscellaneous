/**
 * eg0203.c
 * Determine the max number of files one process can open at one time.
 * Again, we check whether system has OPEN_MAX. If not, we guess one. It is not
 * guaranteed to be good.
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include "../com/comhdr.h"

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

/* if it is undeterminate, we guess one */
#define OPEN_MAX_GUESS 256

static long open_max( void );

int main( int argc, char **argv ) {
  long omax = open_max();
  printf( "open_max is %ld\n", omax );
  return 0;
}

static long open_max( void ) {
  if ( openmax == 0 ) {
    errno = 0;
    if ( (openmax = sysconf( _SC_OPEN_MAX )) < 0 ) {
      if ( errno == 0 ) {
	/* undeterminate, use guessed one */
	openmax = OPEN_MAX_GUESS;
      } else {
	err_sys( "sysconf error\n" );
      }
    }
  }
  return openmax;
}