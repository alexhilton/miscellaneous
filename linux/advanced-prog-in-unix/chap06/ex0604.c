/*
 * ex0604.c
 * see the latest current time representable by time_t.
 */
#include <stdio.h>
#include <time.h>
#include <limits.h>

int main( int argc, char **argv ) {
  /*
   * Though we give it the largest of time_t, after wrapping around, it prints
   * current time.
   */
  unsigned long max_long = ULONG_MAX;
  time_t latest = time( (time_t *) &max_long );
  printf( "%s", ctime( (time_t *) &latest ) );
  return 0;
}
