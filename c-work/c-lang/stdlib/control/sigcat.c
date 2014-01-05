/*
 * sigcat.c
 * a signal handler to catch the segv signal.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler( int s ) {
  if ( s == SIGBUS ) {
    printf( "Now got a bus error signal\n" );
  }
  if ( s == SIGSEGV ) {
    printf( "Now got a segmentation violation signal\n" );
    exit( 1 );
  }
  if ( s == SIGILL ) {
    printf( "Now got an illegal instruction signal\n" );
    exit( 1 );
  }
}

int main() {
  int *p = NULL;
  signal( SIGBUS, handler );
  signal( SIGSEGV, handler );
  signal( SIGILL, handler );
  *p = 0;
  return 0;
}
