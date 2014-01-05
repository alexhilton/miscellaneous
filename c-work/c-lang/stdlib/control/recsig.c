/*
 * recsig.c
 * demostrate how to use setjmp/getjmp to recover from an
 * segmentation fault.
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;

void handler( int s ) {
  if ( s == SIGINT ) {
    printf( "Now got a SIGINT signal\n" );
  }
  longjmp( buf, 1 );
}

int main() {
  signal( SIGINT, handler );
  if ( setjmp( buf ) ) {
    printf( "Back in main\n" );
    return 0;
  } else {
    printf( "First time through\n" );
  }
 loop:
  /* spin here, waiting for ctrl-c */
  goto loop;
}
