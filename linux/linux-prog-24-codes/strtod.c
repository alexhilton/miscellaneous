/*
 * practice of strtod() function.
 * practice of strtod converision function.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ) {
  double lval;
  char *ep, *tmp;
  char snum[] = " -2567.203, 45.00E-10, 39.023E9";

  printf( "snum = '%s'\n", snum );
  tmp = snum;
  lval = strtod( tmp, &ep );
  printf( "lval = %g, tmp = '%s', ep = '%s'\n", lval, tmp, ep );
  tmp = ++ep;
  lval = strtod( tmp, &ep );
  printf( "lval = %g, tmp = '%s', ep = '%s'\n", lval, tmp, ep );
  tmp = ++ep;
  lval = strtod( tmp, &ep );
  printf( "lval = %g, tmp = '%s', ep = '%s'\n", lval, tmp, ep );
  /*
   * when convert this to loop, many problems occur.
   * the termination condition is hard to detect.
   * the following is one implementation, it is buggy.
   */

  /*for ( ep = tmp = snum; *ep != '\0'; tmp = ++ep ) {
    lval = strtol( tmp, &ep, 10 );
    printf( "lval = %ld, tmp = '%s', ep = '%s'\n", lval, tmp, ep );
  }*/
  return 0;
}
