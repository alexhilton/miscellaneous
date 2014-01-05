/*
 * ex0902.c
 * Create a child process and let the child create a new session, we wanna know
 * whether the child is the group leader and no controlling terminal.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  pid_t pid;
  pid_t sid;
  char ch;

  if ( (pid = fork()) < 0 ) {
    err_sys( "fork error" );
  } else if ( pid == 0 ) {
    if ( (sid = setsid()) < 0 ) {
      err_sys( "setsid error" );
    }
    if ( read( STDIN_FILENO, &ch, 1 ) != 1 ) {
      printf( "child has no controlling terminal\n" );
    } else {
      printf( "child is controlling terminal\n" );
    }
    printf( "sid is %d, pid is %d\n", sid, getpid() );
    system( "ps f" );
    exit( 0 );
  }
  sleep( 5 ); /* hope it long enough */
  system( "ps f" );

  return 0;
}
