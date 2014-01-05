/*
 * baseconv.c
 *
 * base conversion of strtol function.
 * specify the base and its number, baseconv will convert it into
 * decimal format. Be careful, if the number if too big, an error
 * will be caused.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  int i;
  char *ep; /* end scan pointer */
  long base; /* conversion base */
  long lval; /* converted long value */

  /*
   * check for command line arguments 
   */
  if ( argc < 2 ) {
    printf( "Usage: %s base 'string' [base 'string']...\n", argv[ 0 ] );
    return 0;
  }

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
    base = strtol( argv[ i ], &ep, 10 );
    if ( *ep != '\0' ) {
      printf( "base error in '%s' near '%s'\n", argv[ i ], ep );
      return 0;
    } else if ( base > 36 || base < 0 ) {
      printf( "Invalid base: %ld\n", base );
      return 0;
    }
  
    if ( ++i >= argc ) {
      printf( "missing conversion string! arg # %d\n", i );
      return 0;
    }
    errno = 0;
    lval = strtol( argv[ i ], &ep, (int) base );
    /* check for some error, such as overflowing */
    if ( errno != 0 ) {
      perror( argv[ i ] );
    } else {
      printf( "%s(%ld) => %ld(10); ep = '%s'\n",
	      argv[ i ], base, lval, ep );
    }
  }
  return 0;
}
