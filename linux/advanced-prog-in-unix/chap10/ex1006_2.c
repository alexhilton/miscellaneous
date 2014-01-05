/*
 * ex1006.c
 * We create a file and write 0 into it, then parent and child increment it
 * alternatively by turn.
 * This is an unsychronized version
 */
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include "../com/comhdr.h"

static void increment( const char *msg, const char *filename );

int main( int argc, char **argv ) {
  int fd;
  if ( (fd = open( *++argv, O_WRONLY | O_CREAT, 0644 )) < 0 ) {
    err_sys( "error on opening file %s", *argv );
  }

  /* Let start the game, parent and child increment the n alternatively */
  tell_wait();
  pid_t pid;
  char buf[ 1024 ];
  memset( buf, 0, 1024 );
  sprintf( buf, "0" );
  write( fd, buf, 1 );
  close( fd );

  int i = 0;
  int ulimit = 100;
  /*
   * Because process cannot share the same memory address, so the program will
   * loop 2*ulimit times, because child's i iterates from 0 to ulimit-1 and
   * parent also iterates from 0 to ulimit-1. Together it is 2*ulimit.
   */
  /* we let parent go first */
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork()" );
  } else if ( pid == 0 ) {
    /* child checking in */
    while ( i < ulimit ) {
      increment( "Child increment", *argv );
      i++;
    }
  } else {
    /* parent cheching in */
    while ( i < ulimit ) {
      increment( "Parent increment", *argv );
      i++;
    }
  }

  return 0;
}

static void increment( const char *msg, const char *filename ) {
  assert( msg != NULL && filename != NULL );
  char buf[ 1024 ];
  size_t bufsize = 1024;
  int fd;
  if ( (fd = open( filename, O_RDONLY )) < 0 ) {
    err_sys( "error on opening file %s", filename );
  }
  int size = read( fd, buf, bufsize );
  buf[ size ] = '\0';
  close( fd );
  int n = atoi( buf );
  n++;
  sprintf( buf, "%d", n );
  size = strlen( buf );
  if ( (fd = open( filename, O_WRONLY )) < 0 ) {
    err_sys( "error on opening file %s", filename );
  }
  write( fd, buf, size );
  printf( "%s with number = %d\n", msg, n );
  close( fd );
}
