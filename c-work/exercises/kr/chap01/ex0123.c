/*
 * ex0123.c
 *
 * remove all the comments from a valid c program.
 * It assumes that the comments do not nest and
 * there is on compilation errors in the C program.
 */
#include <stdio.h>

void recomment( FILE *in, FILE *out, char ch );
void in_comment( FILE *in );
void echo_quote( FILE *in, FILE *out, char ch );

int main( int argc, char *argv[ ] ) {
  char ch;
  FILE *in, *out;

  in = fopen( "input.dat", "r" );
  out = fopen( "output.dat", "w" );
  if ( in == NULL ) {
    perror( "input.dat" );
    return 1;
  }
  if ( out == NULL ) {
    perror( "output.dat" );
    return 1;
  }
 
  while ( ( ch = fgetc( in ) ) != EOF ) {
    recomment( in, out, ch );
  }

  fclose( in );
  fclose( out );

  return 0;
}

/* 
 * Function: recomment
 * 
 * read each character, remove the comments
 */
void recomment( FILE *in, FILE *out, char ch ) {
  char d;

  if ( ch == '/' ) {
    if ( ( d = fgetc( in ) ) == '*' ) {
      in_comment( in ); /* entering comment */
    } else if ( d == '/' ) {
      fputc( d, out );
      recomment( in, out, d );
    } else {
      fputc( ch, out );
      fputc( d, out );
    }
  } else if ( ch == '\'' || ch == '"' ) {
    echo_quote( in, out, ch );
  } else {
    fputc( ch, out );
  }
}

void in_comment( FILE *in ) {
  char ch, d;
  ch = fgetc( in );
  d = fgetc( in );

  while ( ch != '*' || d != '/' ) {
    ch = d;
    d = fgetc( in );
  }
}

void echo_quote( FILE *in, FILE *out, char ch ) {
  char d;

  fputc( ch, out );
  while ( ( d = fgetc( in ) ) != ch ) {
    fputc( d, out );
    if ( d == '\\' ) {
      fputc( fgetc( in ), out );
    }
  }
  fputc( d, out );
}
