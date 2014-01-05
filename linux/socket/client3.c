/*
 * client3.c
 * explore socket
 * We build establishment of connection of this socket through network.
 * We need to do some extra work to make our client/server work
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  int sockfd;
  int len;
  struct sockaddr_in address;
  int result;
  char ch = 'A';

  sockfd = socket( AF_INET, SOCK_STREAM, 0 );

  address.sin_family = AF_INET;
  /* LocalHost */
  address.sin_addr.s_addr = inet_addr( "127.0.0.0" );
  address.sin_port = htons( 9734 );
  len = sizeof( address );

  result = connect( sockfd, (struct sockaddr *) &address, len );
  if ( result == -1 ) {
    perror( "Oops: client1" );
    exit( EXIT_FAILURE );
  }

  write( sockfd, &ch, 1 );
  read( sockfd, &ch, 1 );
  printf( "char from server = %c\n", ch );
  close( sockfd );
  return 0;
}
