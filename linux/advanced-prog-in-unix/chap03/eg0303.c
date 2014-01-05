/**
 * eg0303.c
 * copy standard input to standard output.
 */
#include <unistd.h>
#include "../com/comhdr.h"

/* 
 * it is said that the size of BUFSIZE will affect the efficiency of the program
 * 
 */
#define BUFSIZE 4096

int main( int argc, char **argv ) {
  int n;
  char buf[ BUFSIZE ];

  while ( (n = read( STDIN_FILENO, buf, BUFSIZE )) > 0 ) {
    if ( write( STDOUT_FILENO, buf, n ) != n ) {
      err_sys( "write error" );
    }
  }

  if ( n < 0 ) {
    err_sys( "read error" );
  }
  return 0;
}
