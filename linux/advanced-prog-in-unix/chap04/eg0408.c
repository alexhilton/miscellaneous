/**
 * eg0408.c
 * show you how to use function chdir to change current working directory for a
 * process.
 * Note that current working process is an attribute of a process. As a result,
 * chdir will only affect the current process's current working directory.
 * If you change current working directory for your program, for instance, the
 * shell which runs your program will not be affected.
 */
#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  if ( chdir( "/tmp/" ) < 0 ) {
    fprintf( stderr, "chdir error" );
  }
  printf( "chdir to /tmp succeed\n" );
  return 0;
}
