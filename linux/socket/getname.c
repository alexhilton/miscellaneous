/*
 * getname.c
 * get information about ahost computer.
 */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  char *host, **names, **addrs;
  struct hostent *hostinfo;

  if ( argc == 1 ) {
    char myname[ 256 ];
    /* reserve one for '\0' */
    gethostname( myname, 255 );
    host = myname;
  } else {
    host = *++argv;
  }
  hostinfo = gethostbyname( host );
  if ( hostinfo == NULL ) {
    fprintf( stderr, "cannot get info for host: %s\n", host );
    exit( EXIT_FAILURE );
  }

  /* Print out the messages about this host machine */
  printf( "results for host '%s':\n", host );
  printf( "Name: %s\n", hostinfo->h_name );
  printf( "Aliases:" );
  names = hostinfo->h_aliases;
  while ( names != NULL ) {
    printf( " %s", *names );
    names++;
  }
  printf( "\n" );
  if ( hostinfo->h_addrtype != AF_INET ) {
    fprintf( stderr, "not an IP host!\n" );
    exit( EXIT_FAILURE );
  }
  addrs = hostinfo->h_addr_list;
  while ( *addrs != NULL ) {
    printf( " %s", inet_ntoa( *(struct in_addr *) *addrs ) );
    addrs++;
  }
  printf( "\n" );
  return 0;
}
