/*
 * ex0605.c
 * get current time and print it in the same format used in date(1) using
 * strfmtime.
 */
#include <stdio.h>
#include <time.h>

int main( int argc, char **argv ) {
  time_t now = time( NULL );
  struct tm *nowtm;
  /* 
   * Compared to gmtime( &now ), gmtime returns  GTM or UTC, while localtime 
   * is local timezone.
   */
  nowtm = localtime( &now );
  char timebuf[ 128 ];
  strftime( timebuf, 128, "%a %b %d %X %Z %Y", nowtm );
  printf( "%s\n", timebuf );
  return 0;
}
