/**
 * ex0104.c
 * In error handling fucntions, we have to save a copy of errno in case another
 * error occured during your error handlings.
 * And, you might wander, output functions in <stdio.h> might cause an error,
 * too.
 * Here is the demonstration.
 */
#include <stdio.h>
#include <errno.h>

int main( int argc, char **argv ) {
  int fd;
  if ( (fd = open( "/no/such/file", 0 )) < 0 ) {
    printf( "open error: " );
    printf( "errno = %d\n", errno );
  }
  return 0;
}
