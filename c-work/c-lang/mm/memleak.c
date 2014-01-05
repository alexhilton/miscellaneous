/*
 * a test to memory leak.
 * memleak.c
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  int i;
  for ( i = 0; i < 10; i++ ) {
    malloc( 1024 );
  }
  return 0;
}
