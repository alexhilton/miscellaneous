/*
 * strtok_r() function adventure.
 */
#include <stdio.h>
#include <string.h>

int main( int argc, char *argv[] ) {
  char cmd[ 128 ];
  char *cp;
  char *sp;

  printf( "input a string of command\n" );
  fgets( cmd, sizeof( cmd ), stdin );
  cmd[ strlen( cmd ) - 1 ] = '\0';
  for ( cp = strtok_r( cmd, " ", &sp ); cp != NULL;
	cp = strtok_r( NULL, " ", &sp ) ) {
    printf( "\tcp='%s'", cp );
    printf( "\tsp='%s'\n", sp );
  }

  /* check out what's left in cmd and sp */
  printf( "cmd = '%s', sp = '%s'\n", cmd, sp );
  return 0;
}
