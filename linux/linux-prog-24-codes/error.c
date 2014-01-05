/*
 * Demonstrate two ways of error checking.
 * one is using strerror( errno ).
 *      printf( "%s\n", strerror( errno ) );
 * another alternative is:
 *      perror( str );
 * they are interchangeable.
 * check out the following example.
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main( int argc, char **argv ) {
  FILE *in;
  char fname[ 20 ];
  errno = 0;
  printf( "Input a file you wanna open: " );
  scanf( "%s", fname );
  in = fopen( fname, "r" );
  if ( errno ) {
    printf( "%s\n", strerror( errno ) );
    /*
     * perror is the same to printf( "%s\n", strerror( errno ) );
     * but you can add some extra infor via fname string.
     * the output will be: str: error-msg-by-perror.
     */
    perror( fname ); 
  }
  return 0;
}
