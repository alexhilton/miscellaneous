/**
 * eg0301.c
 * A trick about lseek.
 * We can get current offset of a file by setting argument offset of lseek as 0.
 * 	current = lseek( fd, 0, SET_CUR );
 * We can also use that to test whether standard input is seekable.
 */
#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv ) {
  if ( lseek( STDIN_FILENO, 0, SEEK_CUR ) == -1 ) {
    fprintf( stderr, "Cannot seek\n" );
  } else {
    printf( "Seek OK\n" );
  }
  return 0;
}
