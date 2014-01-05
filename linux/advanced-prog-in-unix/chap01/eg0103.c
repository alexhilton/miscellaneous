/**
 * eg0103.c
 * Re-implement copy using standard IO.
 */
#include <stdio.h>

int main( int argc, char **argv ) {
  int ch;

  while ( (ch = getc( stdin )) != EOF ) {
    if ( putc( ch, stdout ) == EOF ) {
      fprintf( stderr, "output error\n" );
      return 0;
    }
  }

  if ( ferror( stdin ) ) {
    fprintf( stderr, "input error\n" );
    return 0;
  }

  return 0;
}
