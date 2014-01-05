/*
 * ex0506.c
 * when you want to use fsync on a FILE stream, you should use fileno to get the
 * file descriptor from FILE stream structure.
 */
#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  int fd;
  fd = fileno( stdin );
  fsync( fd );
  return 0;
}
