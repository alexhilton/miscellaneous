/*
 * baseconv.c
 *
 * base conversion of strtol function.
 * convert a floating-ponit number string into its corresponding numerical
 * decimal format. Be careful, if the number if too big, an error
 * will be caused.
 * Numerical overflowing error checking capable.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main( int argc, char *argv[] ) {
  int i;
  char *ep; /* end scan pointer */
  double lval; /* converted long value */

  /*
   * check for command line arguments 
   */
  if ( argc < 2 ) {
    printf( "Usage: %s base 'string' [base 'string']...\n", argv[ 0 ] );
    return 0;
  }
  /*printf( "HUGE_VAL is %g\n", HUGE_VAL );*/

  /*
   * processing command line arguments or beginning converting.
   * first get the input base, then get its number
   * then convert into decimal format base on them.
   * For every conversion argv[i] is the input base, and
   * argv[i+1] is the input number.
   * thus the input arguments must be even, otherwise error 
   * occurs.
   */
  for ( i = 1; i < argc; i++ ) {
    errno = 0;
    lval = strtod( argv[ i ], &ep );
    /* check for some error, such as overflowing */
    /* solution 1: using errno directly */
    /*if ( errno != 0 ) {
      perror( argv[ i ] );
    } else {
      printf( "'%s' => %g ep = '%s'\n",
	      argv[ i ], lval, ep );
    }*/

    /* solution 2: using lval, and errno */
    /* more specific */
    if ( lval == 0.0 ) {
      if ( errno == ERANGE ) {
	fprintf( stderr, "Value is too small!\n" );
	return 1;
      }
    } else {
      if ( lval == HUGE_VAL ) {
	if ( errno == ERANGE ) {
	  fprintf( stderr, "upper overflowing\n" );
	  return 1;
	}
      } else if ( lval == -HUGE_VAL ) {
	if ( errno == ERANGE ) {
	  fprintf( stderr, "lower overflowing\n" );
	  return 1;
	}
      }
    }
    printf( "'%s' ==> %g\n", argv[ i ], lval );
  }
  return 0;
}
