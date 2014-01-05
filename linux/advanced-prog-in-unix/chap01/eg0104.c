/**
 * eg0104.c
 * get process id
 */
#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv ) {
  printf( "Hello world from process ID: %d\n", getpid() );
  return 0;
}
