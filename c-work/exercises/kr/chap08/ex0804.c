/**
 * ex0803.c
 * write a simple implementation of fseek.
 * the implementation of fseek is in simio.h.
 * here is the test driver
 */
#include <stdio.h>
#include "simio.h"

/* main program */
int main( int argc, char **argv ) {
  /* copy second file on the middle of first one */
  if ( argc != 3 ) {
    printf( "missing inputs\n" );
    return 0;
  }

  File *in, *out;
  if ( (out = fileopen( *++argv, "w" )) == NULL ||
      (in = fileopen( *++argv, "r" )) == NULL ) {
    printf( "error open file\n" );
    return 0;
  }

  /* position the pointer of first file into its middle */
  fileseek( in, 0L, 2 );
  //lseek( in->fd, 6, 0 );
  char ch;
  while ( (ch = filegetc( in )) != EOF ) {
    fileputc( ch, out );
  }

  /* the print the first file for preview */
  fileclose( in );
  fileclose( out );
  in = fileopen( *--argv, "r" );
  while ( (ch = filegetc( in )) != EOF ) {
    putchar( ch );
  }
  fileclose( in );
  return 0;
}
