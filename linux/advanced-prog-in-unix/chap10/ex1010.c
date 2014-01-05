/*
 * ex1010.c
 * This program calls sleep( 60 ) in an infinite loop. For every five
 * calls--five minutes--we fectch the time of the day and print tm_sec field. We
 * will run the program overnight and see what will happen.
 */
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  int i = 0;
  time_t now;
  struct tm *now_tm;
  while ( 1 ) {
    sleep( 2 );
    if ( i >= 5 ) {
      i -= 5;
      now = time( NULL );
      printf( "Now is %s", ctime( &now ) );
      now_tm = gmtime( &now );
      printf( "tm_sec: %d\n", now_tm->tm_sec );
    }
    i++;
  }

  return 0;
}
