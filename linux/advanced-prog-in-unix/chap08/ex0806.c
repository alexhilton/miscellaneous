/*
 * ex0806.c
 * create a zombie process and call ps to verify it
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  pid_t pid;

  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork()" );
  } else if ( pid == 0 ) {
    printf( "child: I am gone\n" );
    _exit( 0 );
  }

  sleep( 5 ); /* hope this is long enough */
  system( "ps f" );

  return 0;
}
