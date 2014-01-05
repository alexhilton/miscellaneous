/*
 * exercise 0112
 *
 * print one word perline
 * there is one bug: it will print a newline at begin of file
 */
#include <stdio.h>
#include <ctype.h>

const int IN = 1;
const int OUT = 0;
 
int main( int argc, char *argv[] ) {
  if ( argc < 2 ) {
    printf( "Missing input files\n" );
    return 1;
  }
  int i;
  char ch;
  int state;
  FILE *in, *out;
  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[ i ], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    out = fopen( "output.dat", "w" );
    state = OUT;
    while ( (ch = fgetc( in )) != EOF ) {
      if ( isspace( ch ) ) {
	state = OUT;
      } else if ( state == OUT ) {
	state = IN;
	fputc( '\n', out );
	fputc( ch, out );
      } else if ( state == IN ) {
	fputc( ch, out );
      }
    }
    fclose( in );
    fclose( out );
  }
  return 0;
}
