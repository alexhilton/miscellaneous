/*
 * ex1006.c
 * Use tell_wait, tell_parent and tell_child to sychronize parent and child
 * prcoesses.
 * We create a file and write 0 into it, then parent and child increment it
 * alternatively by turn.
 */
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include "../com/comhdr.h"
#include "eg1014.c" /* This is the bad design, bad code */

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
  /* we let parent go first */
  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork()" );
  } else if ( pid == 0 ) {
    /* child checking in */
    while ( i < ulimit ) {
      wait_parent();
      increment( "Child increment", *argv );
      i++;
      /* Never use getpid(), that will send signal to child itself */
      tell_parent( getppid() );
    }
  } else {
    /* parent cheching in */
    while ( i < ulimit ) {
      increment( "Parent increment", *argv );
      i++;
      tell_child( pid );
      wait_child();
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
