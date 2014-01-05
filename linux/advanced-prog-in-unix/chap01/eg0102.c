/**
 * eg0102.c
 * A copy program which copies from stdin to stdout demonstrates hwo to use
 * unbuffered IO: read, write.
 */
#include <unistd.h>
#include <stdio.h>
#include "../com/comhdr.h"

#define BUFSIZE 8192 /* It is said that the definition of BUFSIZE will affect the efficiency */

int main( int argc, char **argv ) {
  int n;
  char buf[ BUFSIZE ];

  while ( (n = read( STDIN_FILENO, buf, BUFSIZE )) > 0 ) {
    if ( write( STDOUT_FILENO, buf, n ) != n ) {
      err_sys( "error while write" );
    }
  }

  if ( n < 0 ) {
    err_sys( "error while reading" );
  }
  return 0;
}
