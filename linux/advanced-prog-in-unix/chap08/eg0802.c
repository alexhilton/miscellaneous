/*
 * eg0802.c
 * example of use vfork call.
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
  printf( "before vfork\n" ); /* we won't flush stdout */
  if ( (pid = vfork()) < 0 ) {
    err_sys( "vfork error" );
  } else if ( pid == 0 ) {
    /* child */
    glob++;
    var++; /* modifying variables */
    _exit( 0 ); /* child process terminates without flushing or shutting IO */
  }
  /*
   * Parent goes here *
   */
  printf( "pid = %d, glob = %d, var = %d\n", getpid(), glob, var );
  return 0;
}
