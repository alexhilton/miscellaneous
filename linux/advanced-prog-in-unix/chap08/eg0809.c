/*
 * eg0809.c
 * print the real user-id and effective user-id.
 */
#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  printf( "real user ID is %d, while effective user id is %d\n", getuid(), geteuid() );
  return 0;
}
