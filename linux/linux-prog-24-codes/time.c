/*
 * time.c
 *
 * venture all the stuffs about time.h lib.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main( int argc, char *argv[] ) {
  time_t td; /* basic time type, long actually */
  /* time structure: Date Components */
  struct tm *dc; /* pointer to Date component */
  char sdate[ 64 ];
  char fmt[ 128 ];
  char *cp;

  time( &td );
  /* 
   * Note that ctime( time_t *t ) will add a '\n' at the
   * end of returned string.
   */
  printf( "Today is: %s", ctime( &td ) );

  /* localtime() and gmtime() */
  /* they are the same */
  dc = localtime( &td );
  printf( "%02d/%02d/%04d %02d:%02d:%02d\n", dc->tm_mon+1,
	  dc->tm_mday, dc->tm_year+1900, dc->tm_hour,
	  dc->tm_min, dc->tm_sec );
  free( dc );

  dc = gmtime( &td );
  printf( "%02d/%02d/%04d %02d:%02d:%02d\n", dc->tm_mon+1,
	  dc->tm_mday, dc->tm_year+1900, dc->tm_hour,
	  dc->tm_min, dc->tm_sec );
  printf( "Today is: %s", asctime( dc ) );
  free( dc );
  /**
   * now check about something about tzset() function.
   * It can set three external variables:
   *    extern long int timezone;
   *    extern char *tzname[2];
   *    extern int daylight;
   */
  int i;
  tzset(); /* make sure external are set */
  i = ( daylight != 0 ? 1 : 0 );
  printf( "Zone is %ld, its name is '%s'\n", timezone, tzname[ i ] );

  /*
   * Next would be mktime() function.
   *    time_t mktime( struct tm *dc );
   */
  /* get current time */
  dc = gmtime( &td );
  time_t tmp = mktime( dc );
  free( dc );
  printf( "td = %ld, while tmp = %ld\n", td, tmp );
  /* another try, we specify a time through mktime() */
  dc = malloc( sizeof( *dc ) );
  dc->tm_mon = 0; /* January */
  dc->tm_mday = 1; /* first day of the month */
  dc->tm_year = 100; /* year 2000 */
  dc->tm_hour = 0; /* Midnight */
  dc->tm_min = 0; /* 0 mins */
  dc->tm_sec = 0; /* 0 sec */
  dc->tm_isdst = 0; /* Not Daylight Saving Time */

  td = mktime( dc );
  printf( "Date: %s", ctime( &td ) );
  free( dc );

  /**
   * next would be strftime() function, which formats the output
   * of time. sort of like sprintf function.
   */
  dc = malloc( sizeof( *dc ) );
  dc->tm_mon = 3; /* April */
  dc->tm_mday = 1; /* 1st */
  dc->tm_year = 100; /* year 2000 */
  dc->tm_hour = 11; /* Just before noon */
  dc->tm_min = 59; /* 59 min */
  dc->tm_sec = 30; /* 30 sec */
  dc->tm_isdst = 0; /* not D.S.T. */

  td = mktime( dc );

  while ( fgets( fmt, sizeof( fmt ), stdin ) != NULL ) {
    if ( (cp = strchr( fmt, '\n' )) != NULL ) {
      *cp = '\0'; /* Remove the newline added by fgets() */
    }
    strftime( sdate, sizeof( sdate ), fmt, dc );
    printf( "Format='%s':\n%s\n\n", fmt, sdate );
  }
  return 0;
}
