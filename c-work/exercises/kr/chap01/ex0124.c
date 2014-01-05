/*
 * ex01241.c
 *
 * check all the unbalanced parenthesises, braces, brackets, double
 * quotes, single quotes and comments.
 */
#include <stdio.h>

int iseven( int n ) {
  if ( ( n & 0x01 ) == 0 ) {
    return 1;
  } 
  return 0;
}

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
  int nbrace = 0; /* number of braces */
  int nbracket = 0; /* number of brackets */
  int ndquote = 0; /* number of double quotes */
  int nsquote = 0; /* number of single quotes */
  int ncomment = 0; /* number of comments */
  int nparenth = 0; /* number of parenthesises */

  char ch, pch; /* current char and previous characters */
  pch = fgetc( in );
  while ( ( ch = fgetc( in ) ) != EOF ) {
    if ( pch == '/' && ch == '*' ) {
      ncomment++;
    } else if ( pch == '*' && ch == '/' ) {
      ncomment--;
    } else if ( pch == '{' ) {
      nbrace++;
    } else if ( pch == '}' ) {
      nbrace--;
    } else if ( pch == '[' ) {
      nbracket++;
    } else if ( pch == ']' ) {
      nbracket--;
    } else if ( pch == '(' ) {
      nparenth++;
    } else if ( pch == ')' ) {
      nparenth--;
    } else if ( pch == '"' ) {
      ndquote++;
    } else if ( pch == '\'' ) {
      nsquote++;
    }
    pch = ch;
  }
  if ( ncomment != 0 ) {
    printf( "Unbalanced comments\n" );
  } 
  if ( nbrace != 0 ) {
    printf( "Unbalanced braces\n" );
  } 
  if ( nbracket != 0 ) {
    printf( "Unbalanced bracket\n" );
  } 
  if ( nparenth != 0 ) {
    printf( "Unbalanced parenthesises\n" );
  } 
  if ( !iseven( ndquote ) ) {
    printf( "Unbalanced double quotes\n" );
  } 
  if ( !iseven( nsquote ) ) {
    printf( "Unbalanced single quotes\n" );
  }

  fclose( in );
  fclose( out );

  return 0;
}
