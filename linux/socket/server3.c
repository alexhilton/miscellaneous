/*
 * server2.c
 * explore socket
 * The establishment of connection of this socket is based on networks.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main( int argc, char **argv ) {
  int server_sockfd;
  int client_sockfd;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  unlink( "server_socket" );
  server_sockfd = socket( AF_INET, SOCK_STREAM, 0 );
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl( INADDR_ANY );
  server_address.sin_port = htons( 9734 );
  server_len = sizeof( server_address );
  bind( server_sockfd, (struct sockaddr *) &server_address, server_len );
  listen( server_sockfd, 5 );
  while ( 1 ) {
    char ch;
    printf( "Server waiting\n" );
    /* Accept a connection */
    client_len = sizeof( client_address );
    client_sockfd = accept( server_sockfd, (struct sockaddr *)
	&client_address, &client_len );
    read( client_sockfd, &ch, 1 );
    ch++;
    write( client_sockfd, &ch, 1 );
    close( client_sockfd );
  }

  return 0;
}
