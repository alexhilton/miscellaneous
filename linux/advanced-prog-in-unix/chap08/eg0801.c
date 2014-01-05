/*
 * eg0801.c
 * example of use fork call.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "../com/comhdr.h"

int glob = 6; /* external variable in initialized data */
char buf[] = "a write to stdout\n";

int main( int argc, char **argv ) {
  int var; /* automatic variable on the stack */
  pid_t pid;

  var = 88;
  if ( write( STDOUT_FILENO, buf, sizeof( buf) - 1 ) != sizeof( buf ) - 1 ) {
    err_sys( "write error" );
  }
  printf( "before fork\n" ); /* we won't flush stdout */
  if ( (pid = fork()) < 0 ) {
    err_sys( "fork error" );
  } else if ( pid == 0 ) {
    /* child */
    glob++;
    var++; /* modifying variables */
  } else {
    sleep( 2 ); /* parent code: wait for child to terminate */
  }
  printf( "pid = %d, glob = %d, var = %d\n", getpid(), glob, var );
  return 0;
}
