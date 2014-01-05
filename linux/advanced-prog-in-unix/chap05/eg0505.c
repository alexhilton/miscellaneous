/*
 * eg0505.c
 * another alternative to create temp file: tempnam.
 */
#include <stdio.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  if ( argc != 3 ) {
    err_quit( "usage: a.out dir prefix" );
  }
  printf( "%s\n", tempnam( *(*++argv) != ' ' ? *argv : NULL,
	*(*++argv) != ' ' ? *argv : NULL ) );
  return 0;
}
