/*
 * eg0805.c
 * demo of race condition.
 */
#include <stdio.h>
#include <unistd.h>
#include "../com/comhdr.h"

static void charactatime( char *buf );

int main( int argc, char **argv ) {
  pid_t pid;

  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    charactatime( "output from child\n" );
  } else {
    charactatime( "output from parent\n" );
  }
  return 0;
}

static void charactatime( char *buf ) {
  char *ptr;
  int ch;
  setbuf( stdout, NULL );
  for ( ptr = buf; ch = *buf++; ) {
    putc( ch, stdout );
  }
}
