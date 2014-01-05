/*
 * ex0710.c
 * see if an automatic variable can be returned.
 * It is perfectly leagal
 */
#include <stdio.h>

int f1( int val );

int main( int argc, char **argv ) {
  int val = 0;
  printf( "before calling f1, val = %d\n", val );
  val = f1( val );
  printf( "from f1, val = %d\n", val );
  return 0;
}

int f1( int val ) {
  int *p;
  if ( val == 0 ) {
    int val = 4;
    p = &val;
  }
  return (*p + 1);
}
