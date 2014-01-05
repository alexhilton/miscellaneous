/*
 * ex0121.c
 *
 * replace strings of blanks by the minimum number of tabs
 * ans blanks to achieve the same spacing. Use the same 
 * tab stops as for detab.
 */
#include <stdio.h>

#define TABINC 8

int main( int argc, char *argv[ ] ) {
  FILE *in, *out;

  in = fopen( "output.dat", "r" );
  if ( in == NULL ) {
    perror( "output.dat" );
    return 1;
  }
  out = fopen( "input.dat", "w" );
  if ( out == NULL ) {
    perror( "input.dat" );
    return 1;
  }

  char ch; /* current char */
  int nb; /* number of blanks necessary */
  int nt; /* number of tabs necessary */
  int pos; /* current position in current line */
  nb = 0;
  nt = 0;
  for ( pos = 0; (ch = fgetc( in )) != EOF; pos++ ) {
    if ( ch == ' ' ) {
      if ( pos % TABINC != 0 ) {
	nb++; /* not reach tab stop yet, increments nb */
      } else {
	nb = 0; /* reach tab stop, clear nb, increments nt */
	nt++;
      }
    } else {
      while ( nt > 0 ) {
	fputc( '\t', out ); /* enter tabs */
	nt--;
      }
      if ( ch == '\t' ) {
	nb = 0; /* forget about the blanks */
      } else {
	while ( nb > 0 ) {
	  fputc( ' ', out );
	  nb--;
	}
      }
      fputc( ch, out );
      if ( ch == '\n' ) {
	pos = 0;
      } else if ( ch == '\t' ) {
	pos = pos + ( TABINC - pos % TABINC ) - 1;
      }
    }
  }
  fclose( in );
  fclose( out );

  return 0;
}
