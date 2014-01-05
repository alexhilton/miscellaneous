/*
 * ex0801.c
 * In vfork(), the child will copy the parent's memory address. So when
 * terminate the child with exit, we should use _exit instead of exit. Because
 * exit might flush the I/O streams and close I/O streams(depends on
 * implementations).
 * This exercise is to verify what will happend when using exit to terminate
 * child. And flush and close the streams explictly if implementation of exit
 * does not.
 * We see that, our implementation does not close the streams. After we close
 * stream explictly, printf fails.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
    fclose( stdout );
    exit( 0 ); /* child process terminates with flushing or shutting IO */
  }
  /*
   * Parent goes here *
   */
  char buf[ 10 ];
  int i = printf( "pid = %d, glob = %d, var = %d\n", getpid(), glob, var );
  sprintf( buf, "result of printf is '%d'\n", i );
  write( STDOUT_FILENO, buf, strlen( buf ) );
  return 0;
}
