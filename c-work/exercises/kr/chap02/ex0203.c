/*
 * ex0203.c
 *
 * implement a function htoi( char hstr[ ] ) to convert a string
 * of hexical into its corresponding integer.
 * with an optional '0x' or '0X' 
 */
#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 128
#define BASE 16

int htoi( char hstr[ ] );

int main( int argc, char *argv[ ] ) {
  FILE *in, *out;

  in = fopen( "input.dat", "r" );
  if ( in == NULL ) {
    perror( "input.dat" );
    return 1;
  }
  out = fopen( "output.dat", "w" );
  if ( out == NULL ) {
    perror( "output.dat" );
    return 1;
  }
  char str[ MAX_SIZE ];
  int n;

  while ( fscanf( in, "%s", str ) != EOF ) {
    n = htoi( str );
    fprintf( out, "%x\n", n );
  }

  fclose( in );
  fclose( out );

  return 0;
}

/*
 * Function: htoi
 *
 * Convert string of hexical digits into corresponding integer
 * with an optional beginning '0x' or '0X'.
 * It assumes that the input string are valid hexical string, i.e.
 * digits '0' ~ '9', 'a'~'f' or 'A'~'F'.
 */
int htoi( char hstr[ ] ) {
  int n = 0;
  int i = 0;
  if ( hstr[ 0 ] == '0' && tolower( hstr[ 1 ] ) == 'x' ) {
    i = 2;
  }
  for ( ; hstr[ i ] != '\0'; i++ ) {
    n *= BASE;
    if ( isdigit( hstr[ i ] ) ) {
      n += hstr[ i ] - '0';
    } else {
      n += tolower( hstr[ i ] ) - 'a' + 10;
    }
  }
  return n;
}
