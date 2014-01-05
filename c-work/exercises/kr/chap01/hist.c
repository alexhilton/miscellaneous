/*
 * hist.c
 *
 * this is the right version of it.
 * Print the word length distributions using horizontal histogram and
 * vertical histogram.
 * But there are some bugs that need to be modified and improved.
 * 	#1: the width and the format of index
 * 	#2: the limits of max hist and max length
 * 	#3: the print methods and index printing methods could be
 * 	    abstracted as a new independent interface.
 */
#include <stdio.h>
#include "hist.h"

#define MAX_LENGTH 15 /* max length of a word */

static int maxelem( int a[ ], int size ) {
  int i, j = 0;
  for ( i = 1; i < size; i++ ) {
    if ( a[ j ] < a[ i ] ) {
      j = i;
    }
  }
  return a[ j ];
}

int hhist( FILE *out, int wlc[ ], int size, int step ) {
  int maxvalue = 0;
  int i;
  maxvalue = maxelem( wlc, size );
  int len; /* length of a bar */
  int unit = MAX_HIST / maxvalue;
  int begin = 0; /* begin of an interval */
  int end = step; /* end of an interval */

  /* drawing the histogram */
  for ( i = 0; i < size; i++ ) {
    /* print index */
    fprintf( out, "%02d-%02d |", begin, end );
    begin = end;
    end += step;
    /* print the histogram or the bar */
    if ( wlc[ i ] > 0 ) {
      len = unit * wlc[ i ];
      if ( len <= 0 ) {
	len = 1; /* round it to 1 */
      } 
    } else {
      len = 0; /* no way for less that 0 */
    }
    while ( len > 0 ) {
      fputc( '*', out );
      len--;
    }
    fputc( '\n', out );
  }
  return 0;
}

int vhist( FILE *out, int wlc[ ], int size, int step ) {
  int maxvalue = 0;
  int i, j;
  maxvalue = maxelem( wlc, size );
  int unit = MAX_HIST / maxvalue;
  int begin = 0;
  int end = step;

  /* drawing the histogram */
  for ( i = MAX_HIST; i > 0; i-- ) {
    for ( j = 0; j < size; j++ ) {
      if ( wlc[ j ] * unit >= i ) {
	fprintf( out, "  *  " );
      } else {
	fprintf( out, "     " );
      }
      fputc( ' ', out );
    }
    fputc( '\n', out );
  }

  /* print index */
  for ( i = 0; i < size; i++ ) {
    fprintf( out, "======" );
  }
  fputc( '\n', out );

  for ( i = 0; i < size; i++ ) {
    fprintf( out, "%02d-%02d", begin, end );
    fputc( ' ', out );
  }
  fputc( '\n', out );
  return 0;
}
