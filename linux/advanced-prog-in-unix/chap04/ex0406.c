/*
 * ex0406.c
 * implement cp without copying holes of a file, if any.
 * The strategy is that we copy byte by byte, if this char is 0,
 * we ignore it.
 * The efficiency is bad, since we use read and write one char
 * a time.
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main( int argc, char **argv ) {
  char ch;
  int n, fd1, fd2;
  if ( argc != 3 ) {
    printf( "Usage: cp file1 file2\n" );
    return 0;
  }
  if ( (fd1 = open( *++argv, O_RDONLY )) < 0 ) {
    fprintf( stderr, "open file '%s' failed: %s\n", *argv, strerror( errno ) );
    return 0;
  }
  if ( (fd2 = creat( *++argv, 0644 )) < 0 ) {
    fprintf( stderr, "create file '%s' failed: %s\n", *argv, strerror( errno ) );
    return 0;
  }
  while ( (n = read( fd1, &ch, 1 )) > 0 ) {
    if ( ch != 0 ) {
      if ( write( fd2, &ch, n )  != n ) {
	fprintf( stderr, "write error\n" );
	return 0;
      }
    }
  }
  close( fd1 );
  close( fd2 );
  return 0;
}
