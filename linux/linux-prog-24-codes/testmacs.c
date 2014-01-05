/*
 * testmacs.c -- exercise the function defined in filefch.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "filefch.h"

int main( int argc, char **argv )
{
  FILE *fp;

  /* this call will work */
  if ( open_file( &fp, "foo_bar", "w", __LINE__, __FILE__ ) ) {
    exit( EXIT_FAILURE );
  } else {
    fputs( "this text proves we scribbled in the file.\n", fp );
    fclose( fp );
  }

  /* this call will fail */
  if ( open_file( &fp, "bar_baz", "r", __LINE__, __FILE__ ) ) {
    exit( EXIT_FAILURE );
  } else {
    fclose( fp );
  }

  return ( 0 );
}
