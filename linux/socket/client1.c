/*
 * client1.c
 * explore socket
 * The establishment of connection of this socket is based on unix file system.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  int sockfd;
  int len;
  struct sockaddr_un address;
  int result;
  char ch = 'A';

  sockfd = socket( AF_UNIX, SOCK_STREAM, 0 );

  address.sun_family = AF_UNIX;
  strcpy( address.sun_path, "server_socket" );
  len = sizeof( address );

  result = connect( sockfd, (struct sockaddr *) &address, len );

  if ( result == -1 ) {
    perror( "Oops: client1" );
    exit( EXIT_FAILURE );
  }

  write( sockfd, &ch, 1 );
  read( sockfd, &ch, 1 );
  printf( "char from server =  %c\n", ch );
  close( sockfd );
  return 0;
}
