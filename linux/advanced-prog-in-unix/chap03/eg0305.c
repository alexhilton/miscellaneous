/**
 * eg0305.c
 * copy standard input to standard output.
 * With one or more fd flags set
 */
#include <unistd.h>
#include <fcntl.h>
#include "../com/comhdr.h"

/* 
 * it is said that the size of BUFSIZE will affect the efficiency of the program
 * 
 */
#define BUFSIZE 4096

/*
 * turn on one or more of the file status flags for a descriptor.
 */
void set_fl( int fd, int flags );

int main( int argc, char **argv ) {
  int n;
  char buf[ BUFSIZE ];

  /* turn on flag O_SYNC so that the write can be done to disk synchronously */
  set_fl( STDOUT_FILENO, O_SYNC );
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

void set_fl( int fd, int flags ) {
  int val;
  if ( (val = fcntl( fd, F_GETFL, 0 )) < 0 ) {
    err_sys( "fcntl F_GETFL error" );
  }
  val |= flags;
  if ( fcntl( fd, F_SETFL, val ) < 0 ) {
    err_sys( "fcntl F_SETFL error" );
  }
}
