/*
 * ex01231.c
 *
 * remove all the comments from a valid C program.
 * assuming that, commente do not nest and the input file (C program) should
 * be valid, i.e. no compilation errors.
 * ### there is one bug, which is the program will always print a
 *   '/', because when entering the comments and leaving the comments
 *   when ch is '/', the state is out, so '/' will be printed.
 *   If you print pch, then the leaving '/' will be printed, if
 *   you print ch, entering '/' will be printed. Here we print
 *   pch, and replacing ch with ' ' when leaving the comment
 */
#include <stdio.h>

#define IN 1 /* inside a comment */
#define OUT 0 /* out of a comment */

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
  char ch; /* current char */
  char pch; /* previous char */
  int state = OUT;
  pch = fgetc( in );
  if ( pch == EOF ) {
    fclose( in );
    fclose( out );
    return 1;
  }
  while ( ( ch = fgetc( in ) ) != EOF ) {
    if ( pch == '/' && ch == '*' ) {
      state = IN;
    } else if ( state == OUT ) {
      fputc( pch, out );
    } else if ( state == IN && pch == '*' && ch == '/' ) {
      state = OUT;
      ch = ' ';
    }
    pch = ch;
  }
  fclose( in );
  fclose( out );

  return 0;
}
