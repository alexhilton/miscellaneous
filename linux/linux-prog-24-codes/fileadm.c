/*
 * fileadm.c
 *
 * Learn some tricks about file admininstration.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  char src[ 128 ], dst[ 128 ];
  char *buf;

  printf( "Input source file: " );
  scanf( "%s", src );
  printf( "Input destination file: " );
  scanf( "%s", dst );

  /* build a link */
  if ( link( src, dst ) != 0 ) {
    perror( src );
    perror( dst );
    return 0;
  }

  /* delete an existing link */
  printf( "which link you wanna delete: " );
  scanf ( "%s", src );
  if ( unlink( src ) != 0 ) {
    perror( src );
    return 0;
  }

  /**
   * get current working directory.
   * getcwd().
   * this is usual way and it is preferable.
   */
  if ( getcwd( src, sizeof( src ) ) == NULL ) {
    printf( "%s\n", strerror( errno ) );
    return 0;
  } else {
    printf( "%s\n", src );
  }

  /* another solution to getcwd() */
  /*
   * buf is a pointer to char without allocating memory.
   * But do remember to free memory it occupied.
   * note the arguemts of getcwd().
   * This solution is not portable and may not work sometimes.
   * It is not recommended to use.
   */
  buf = getcwd( NULL, -1 );
  if ( buf == NULL ) {
    perror( "getcwd()" );
    return 0;
  } else {
    printf( "%s\n", buf );
    free( buf ); /* do remember this */
  }

  return 0;
}
