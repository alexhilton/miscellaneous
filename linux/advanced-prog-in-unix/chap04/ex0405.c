/*
 * ex0405.c
 * Verify whether there is a directory whose size is 0, and whether there is a
 * symbolic link whose size is 0, too.
 * The result is that there is no way a directory and a symbolic link's size are
 * 0.
 */
#include <stdio.h>
#include <sys/stat.h>

int main( int argc, char **argv ) {
  struct stat buf;
  while ( --argc > 0 ) {
    if ( lstat( *++argv, &buf ) < 0 ) {
      fprintf( stderr, "lstat error on file '%s'\n", *argv );
      continue;
    }
    printf( "file size of '%s' is %ld\n", *argv, buf.st_size );
  }
  return 0;
}
