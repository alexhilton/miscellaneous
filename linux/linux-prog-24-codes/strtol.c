/*
 * practice of strtol() function.
 * and some tricks to convert from string to numeric number
 * with some error checking.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ) {
  long lval;
  char *ep, *tmp;
  char snum[] = " -2567, 45, 39";

  printf( "snum = '%s'\n", snum );
  tmp = snum;
  lval = strtol( tmp, &ep, 10 );
  printf( "lval = %ld, tmp = '%s', ep = '%s'\n", lval, tmp, ep );
  tmp = ++ep;
  lval = strtol( tmp, &ep, 10 );
  printf( "lval = %ld, tmp = '%s', ep = '%s'\n", lval, tmp, ep );
  tmp = ++ep;
  lval = strtol( tmp, &ep, 10 );
  printf( "lval = %ld, tmp = '%s', ep = '%s'\n", lval, tmp, ep );
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
