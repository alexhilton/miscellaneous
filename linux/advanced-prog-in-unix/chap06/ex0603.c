/*
 * ex0603.c
 * learn system call: gethostname and uname.
 * The output of system command uname(1) has nore fields about CPU's info and
 * publisher of kernel.
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  char host[ 128 ];
  if ( gethostname( host, 128 ) != 0 ) {
    err_sys( "gethostname failed" );
  }
  struct utsname info;
  if ( uname( &info ) != 0 ) {
    err_sys( "uname error" );
  }
  printf( "%s, %s, %s, %s, %s\n", info.sysname, info.nodename, info.release, info.version,
      info.machine );
  return 0;
}
