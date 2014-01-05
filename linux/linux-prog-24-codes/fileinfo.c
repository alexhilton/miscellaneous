/*
 * fileinfo.c
 *
 * Some tricks to get information about a file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

void print_info( struct stat *info );

int main( int argc, char *argv[] ) {
  struct stat buf;
  int i;

  if ( argc < 2 ) {
    printf( "Missing input files\n" );
    return 0;
  }

  for ( i = 1; i < argc; i++ ) {
    /*
     * here you will easily create an bug.
     * the second argument is 'struct stat *buf', and you prefer pointer
     * to actual variable, since you may write as 'stat( argv[i], buf )'
     * and declare buf as 'struct stat *buf'.
     * Do you still remember the bug we have discussed about pointer
     * arguments. The function can change the contents a pointer points
     * to, but cannot change the value of pointer itself, such as allocating
     * freeing spaces for pointer arguments.
     * Here if you use pointer directly, who is responsible for allocating 
     * spaces. Since function 'stat' just fill some information into
     * structure 'buf'.
     * the same problem may occur in other kind of structure arguments.
     * another advantage of using actual structure is that you don't have to
     * worry about freeing spaces.
     */
    if ( stat( argv[ i ], &buf ) != 0 ) {
      perror( argv[ i ] );
      continue;
    }
    printf( "File: '%s':\n", argv[ i ] );
    print_info( &buf );
  }

  return 0;
}

void print_info( struct stat *buf ) {
  if ( S_ISLNK( buf->st_mode ) ) {
    printf( "It is a symbolic link\n" );
  }
  if ( S_ISREG( buf->st_mode ) ) {
    printf( "It is a normal file\n" );
  }
  if ( S_ISDIR( buf->st_mode ) ) {
    printf( "It is a directory\n" );
  }
  printf( "block size is %ld\n", buf->st_blksize );
  printf( "number of blocks is %ld\n", buf->st_blocks );
  printf( "created time is: %s", ctime( &buf->st_ctime ) );
  printf( "last visiting is: %s", ctime( &buf->st_atime ) );
  printf( "last modifying is: %s", ctime( &buf->st_mtime ) );
  putchar( '\n' );
}
