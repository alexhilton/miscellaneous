/*
 * ex0402.c
 * What is umask is 0777.
 * This will turn off all bits in st_mode.
 */
#include <stdio.h>
#include <sys/stat.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP \
    | S_IWGRP | S_IROTH | S_IWOTH)

int main( int argc, char **argv ) {
  umask( 0777 ); /* this will turn off all bits when creating file */
  if ( creat( "foo", RWRWRW ) < 0 ) {
    fprintf( stderr, "creat error on file foo" );
  }
  if ( creat( "bar", RWRWRW ) < 0 ) {
    fprintf( stderr, "creat error on file bar" );
  }
  return 0;
}
