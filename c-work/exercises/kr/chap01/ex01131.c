/*
 * exercise 0113
 *
 * print horizontal and vertical histograms for lengths of words
 * in input.
 * You have missunderstood the meaning of exercise. You are asked
 * to print a statistical histogram of word-length distribution
 * that is how many word that length is 3, how many words whose length
 * is 5 and etc.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "histogram.h"

const int IN = 1;
const int OUT = 0;

#define MAX_SIZE 1000 /* max size of array of word length */

static int wlength( FILE *in, int a[ ] );

int main( int argc, char *argv[ ] ) {
  if ( argc < 2 ) {
    printf( "Missing input files!\n" );
    return 1;
  }
  int i;
  FILE *in, *out;
  int a[ MAX_SIZE ];
  int size;
  int start, end;
  int rc1, rc2; /* return code */
  for ( i = 1; i < argc; i++ ) {
    in = fopen( argv[ i ], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    out = fopen( "output.dat", "w" );
    size = wlength( in, a );
    start = 0;
    end = 0;
    rc1 = hhistogram( out, a, size, start, end );
    rc2 = vhistogram( out, a, size, start, end );
    if ( rc1 != 0 || rc2 != 0 ) {
      printf( "Error Occured!\n" );
      return 1;
    }

    fclose( in );
    fclose( out );
  }
  return 0;
}

static int wlength( FILE *in, int a[ ] ) {
  int i = 0;
  char ch;
  int state;
  int size;
  memset( a, 0, 1000 * sizeof( int ) );
  state = OUT;
  while ( (ch = fgetc( in )) != EOF ) {
    if ( isspace( ch ) ) {
      state = OUT;
    } else if ( state == OUT ) {
      state = IN;
      i++;
    } else if ( state == IN ) {
      a[ i-1 ]++;
    }
  }
  size = i;
  for ( i = 0; i < size; i++) {
    a[ i ]++;
  }
  return size;
}
