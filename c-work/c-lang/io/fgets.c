/*
 * this file explodes some tricks about fgets function.
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main( void ) {
  char line[ 128 ];
  int len;
  FILE *in, *out;
  in = fopen( "input.dat", "r" );
  out = fopen( "output.dat", "w" );
  assert( in );
  assert( out );
  while ( fgets( line, sizeof( line ), in ) != NULL ) {
    /* you can also use line[ 1 ] == '\0' to test blank line */
    if ( line[ 0 ] == '\n' ) {
      fprintf( out, "==================================================\n" );
      fprintf( out, "this is a white line\n" );
      len = strlen( line );
      fprintf( out, "the length of this line is %d\n", len );
      fprintf( out, "char is '%c'\n", line[ 0 ] );
      fprintf( out, "==================================================\n\n" );
    }
    len = strlen( line );
    fprintf( out, "==================================================\n" );
    fprintf( out, "the line you've just entered is '%s'\n", line );
    fprintf( out, "the length of it is %d\n", strlen( line ) );
    fprintf( out, "first two chars '%c' and '%c'\n", line[ 0 ], line[ 1 ] );
    fprintf( out, "last two chars '%c' and '%c'\n", line[len-2], line[len-1] );
    fprintf( out, "==================================================\n\n" );
  }
  fclose( in );
  fclose( out );
  return 0;
}
