/*
 * venture in strtok() function.
 */
#include <string.h>
#include <stdio.h>

int main( int argc, char *argv[] ) {
  char cmd[ 120 ];
  char *cp;

  printf( "Input a string of comand\n" );
  fgets( cmd, sizeof( cmd ), stdin );
  cmd[ strlen( cmd ) - 1 ] = '\0';

  for ( cp = strtok( cmd, " " ); cp != NULL; cp = strtok( NULL, " " ) ) {
    printf( "\t'%s'\n", cp );
  }

  /* check out whether cmd exists or not */
  printf( "Check out whether 'cmd' exists or not\n" );
  printf( "content of cmd is '%s'\n", cmd );
  return 0;
}
