/**
 * ex0302.c
 * Write an implementation of dup2.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../com/comhdr.h"

static int mydup2( int fd, int new_fd );

int main( int argc, char **argv ) {
  int fd = 10;
  char buf[] = "Hello world\n";
  int n = strlen( buf );
  if ( (fd = mydup2( STDOUT_FILENO, fd )) < 0 ) {
    err_sys( "mydup2 error" );
  }
  if ( write( fd, buf, n ) != n ) {
    err_sys( "write error" );
  }
  close( fd );
  return 0;
}

/* implement function: dup2 */
/*
 * return the fd specified by new_fd.
 * If fd == new_fd, we return fd.
 * Otherwise, we dup fd until get new_fd.
 * This is feasible, since dup returns the lowest avialable fd.
 * We keep duping until match( or up to ) new_fd.
 * If fd > new_fd, we report error. Since dup returns the lowest available fd.
 * There is no way to dup a smaller one.
 * Return -1 on error.
 */
static int mydup2( int fd, int new_fd ) {
  if ( fd == new_fd ) {
    return fd;
  } else if ( fd > new_fd ) {
    /* there is no way to dup a smaller one, report error */
    return -1;
  }

  close( new_fd );
  int tmp_fd = fd;
  while ( tmp_fd < new_fd ) {
    if ( (tmp_fd = dup( fd )) < 0 ) {
      return -1;
    }
  }
  /* now we have found new fd == new_fd */
  return new_fd;
}
