/*
 * ex0113m
 *
 * this is the right version of it.
 * Print the word length distributions using horizontal histogram and
 * vertical histogram.
 * But there are some bugs that need to be modified and improved.
 * 	#1: the width and the format of index
 * 	#2: the limits of max hist and max length
 */
#include <stdio.h>
#include "hist.h"

#define MAX_LENGTH 15 /* max length of histogram */
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int main( int argc, char *argv[ ] ) {

  char ch; /* current char */
  int i, state; /* current state: inside or outside a word */
  int wordlen; /* length of a word */
  /* word length counter, recording word number of a length */
  int wlc[ MAX_LENGTH + 1 ]; 
  int rc; /* return code for drawing histograms */
  FILE *in, *out;

  in = fopen( "ex0113m.c", "r" );
  out = fopen( "output.dat", "w" );
  if ( in == NULL || out == NULL ) {
    perror( "In Out" );
    return 1;
  }

  state = OUT;
  wordlen = 0;
  for ( i = 0; i <= MAX_LENGTH; i++ ) {
    wlc[ i ] = 0;
  }

  while ( (ch = fgetc( in )) != EOF ) {
    if ( ch == ' ' || ch == '\n' || ch == '\t' ) { /* white spaces */
      state = OUT;
      if ( wordlen > 0 ) {
	if ( wordlen < MAX_LENGTH ) {
	  wlc[ wordlen ]++; /* one more word whose length is wordlen */
	} else {
	  /* one more word whose length is overflowing */
	  wlc[ MAX_LENGTH ]++;
	}
	wordlen = 0; /* prepare for next word */
      }
    } else if ( state == OUT ) {
      state = IN;
      wordlen = 1; /* beginning of a new word */
    /* equal to state == IN, not white spaces, not OUT, only be IN */
    } else { 
      wordlen++;
    }
  }

  rc = hhist( out, wlc, MAX_LENGTH+1, 1 );
  if ( rc > 0 ) {
    printf( "Error occured when drawing histogram\n" );
    return 1;
  }
  for ( i = 0; i <= MAX_LENGTH; i++ ) {
    printf( " %02d ", wlc[ i ] );
  }
  putchar( '\n' );

  fclose( in );
  fclose( out );
  return 0;
}
