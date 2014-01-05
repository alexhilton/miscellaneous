/*
 * timedemo.c
 * a program to play some tricks with the time.h interface.
 */
#include <stdio.h>
#include <time.h>

int main( void ) {
  time_t time = 0x7fffffff; /*biggest time*/
  printf( "biggest time is: %s\n", ctime( &time ) );
  printf( "\n\t *** another version ***\n" );
  printf( "time is: %s\n", asctime( gmtime( &time ) ) );
  return 0;
}
