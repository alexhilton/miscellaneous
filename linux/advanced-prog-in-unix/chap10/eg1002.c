/*
 * eg1002.c
 * demo of re-entrant system call
 * This doesnot work
 */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pwd.h>
#include "../com/comhdr.h"

static void my_alarm( int signo ) {
  struct passwd *root;
  printf( "in signal handler\n" );
  if ( (root = getpwnam( "root" )) == NULL ) {
    err_sys( "error on getpwent" );
  }
  alarm( 1 );
}

int main( int argc, char **argv ) {
  struct passwd *alex;

  signal( SIGALRM, my_alarm );
  alarm( 1 );
  while ( 1 ) {
    if ( (alex = getpwnam( "alex" )) == NULL ) {
      err_sys( "error on getpwnam( 'alex' )" );
    } else if ( strcmp( alex->pw_name, "alex" ) != 0 ) {
      printf( "return value corrupted: return '%s'\n", alex->pw_name );
    }
  }
  return 0;
}
