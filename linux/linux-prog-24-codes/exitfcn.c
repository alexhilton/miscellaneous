/*
 * exitfcn.c -- Fun with atexit
 */
#include <stdio.h>
#include <stdlib.h>

void f_atexit(
  void 
);

int main( int argc, char **argv )
{
  puts( "this msg from main( ) " );
  if ( atexit( f_atexit ) != 0 ) {
    fprintf( stderr, "failed to register f_atexit()\n" );
    exit( EXIT_SUCCESS );
  }

  puts( "exiting..." );

  exit( EXIT_SUCCESS );
}

void f_atexit(
  void
) {
  puts( "this msg from f_atexit()\n" );
}
