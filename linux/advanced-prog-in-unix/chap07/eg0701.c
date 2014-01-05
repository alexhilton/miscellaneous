/*
 * eg0701.c
 * Use atexit to register some function to atexit, which will be called when
 * exiting the process.
 */
#include <stdio.h>
#include <stdlib.h>
#include "../com/comhdr.h"

static void atexit1( void );
static void atexit2( void );

int main( int argc, char **argv ) {
  if ( atexit( atexit2 ) != 0 ) {
    err_sys( "cannot register atexit2" );
  }
  if ( atexit( atexit1 ) != 0 ) {
    err_sys( "cannot register atexit1" );
  }
  if ( atexit( atexit1 ) != 0 ) {
    err_sys( "Cannot register atexit1" );
  }
  printf( "main function terminate\n" );
  return 0;
}

static void atexit1( void ) {
  printf( "atexit1 executed\n" );
}

static void atexit2( void ) {
  printf( "atexit2 executed\n" );
}
