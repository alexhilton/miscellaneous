/*
 * tmpnamebuf.c
 *
 * call tmpnam() function by buffer.
 * one of the advantages using buffer is that you can save temporary file
 * as long as you wish if you create it in buffer.
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  char tmp_pathname[ L_tmpnam ];
  FILE *in;

  if ( tmpnam( tmp_pathname ) == NULL ) {
    perror( tmp_pathname );
    return 0;
  }

  printf( "Using temp file '%s' \n", tmp_pathname );

  if ( (in = fopen( tmp_pathname, "r" )) == NULL ) {
    perror( tmp_pathname );
    return 0;
  }

  return 0;
}
