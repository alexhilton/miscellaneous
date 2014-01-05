/**
 * eg0107.c
 * print userid and group id
 */
#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  printf( "user ID = %d, group ID = %d\n", getuid(), getgid() );
  return 0;
}
