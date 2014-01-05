/*
 * ex0120.c
 *
 * replace tab ('\t') in the input with proper number of spaces
 * We process the input line by line
 */
#include <stdio.h>

#define TABUL 8 /* tabulent */

/* replace tabs with the proper number of blanks */
int main( int argc, char *argv[ ] ) {
  char ch; /* current char */
  int nb; /* number of blanks needed to fill */
  int pos; /* current position in input per line */
  FILE *in, *out;

  in = fopen( "input.dat", "r" );
  if ( in == NULL ) {
    perror( "input.dat" );
    return 1;
  }
  out = fopen( "output.dat", "w" );

  nb = 0;
  pos = 0;
  while ( ( ch = fgetc( in ) ) != EOF ) {
    if ( ch == '\t' ) {
      /* 
       * number of blanks neccessary to replace tab
       * pos / TABUL is previous tab stop and pos % TABUL is
       * the number of letters in this tabulent, so we need
       * tabul - pos%tabul blanks to reach next tab stop
       */
      nb = TABUL -  pos % TABUL;
      while ( nb > 0 ) {
	fputc( ' ', out );
	pos++;
	nb--;
      }
    } else if ( ch == '\n' ) {
      fputc( '\n', out );
      pos = 0;
    } else {
      fputc( ch, out );
      pos++;
    }
  }

  fclose( in );
  fclose( out );
  return 0;
}
