/*
 * ex803.c
 * solution ex0803
 * the implementation of fclose, fflush and _flushbuf are in simio.c
 * this program is to test it
 */
#include "simio.h"
#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv ) {
  /* copy first file onto screen and second file */
  if ( argc != 3 ) {
    printf( "error: insufficient inputs\n" );
    return 0;
  }
  File *in = fileopen( *++argv, "r" );
  File *out = fileopen( *++argv, "w" );
  //File *out1 = fileopen( *++argv, "w" );
  if ( in == NULL || out == NULL ) { //|| out1 == NULL ) {
    printf( "error opening fiels\n" );
    return 0;
  }

  /* test getc, putc, _flushbuf, _fillbuf and fclose */
  //char ch;
  //while ( (ch = filegetc( in )) != EOF ) {
    //putch( ch );
    //putchar( ch );
    //fileputc( ch, out );
  //}

  /* rewind to begin of file */
  //fseek( in, 0L, 0 );
  //lseek( in->fd, 0L, 0 );
  
  /* copy to a file */
  char str[ 128 ];
  while ( filegets( str, sizeof( str ), in ) != NULL ) {
    fputs( str, stdout );
    fileputs( str, out );
  }
  fileclose( in );
  fileclose( out );
  //fileclose( out1 );
  return 0;
}
