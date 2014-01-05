/*
 * histogram.c
 *
 * implementation of interface histogram.h
 */
#include <stdio.h>
#include "histogram.h"

int hhistogram( FILE *out, int a[ ], int size, int start, int end ) {
  int i, j;
  for ( i = 0; i < size; i++ ) {
    fprintf( out, "%02d-%02d|", i, i );
    for ( j = 0; j < a[ i ]; j++ ) {
      fputc( '*', out );
    }
    fputc( '\n', out );
  }
  return 0;
}

int hshistogram( FILE *out, int a[ ], int size, char *name[ ] ) {
  int i, j;
  for ( i = 0; i < size; i++ ) {
    fprintf( out, "%5s|", name[ i ] );
    for ( j = 0; j < a[ i ]; j++ ) {
      fputc( '*', out );
    }
    fputc( '\n', out );
  }
  return 0;
}

int vhistogram( FILE *out, int a[ ], int size, int start, int end ) {
  int i, j = 0;
  for ( i = 1; i < size; i++ ) {
    if ( a[ j ] < a[ i ] ) {
      j = i;
    }
  }
  int cutoff = a[ j ]; /* max value of a[ ] */
  while ( cutoff > 0 ) {
    for ( i = 0; i < size; i++ ) {
      if ( cutoff == a[ i ] ) {
	fprintf( out, "  *  " );
	a[ i ]--;
      } else {
	fprintf( out, "     " );
      }
      fputc( ' ', out );
    }
    fputc( '\n', out );
    cutoff--;
  }
  for ( i = 0; i < size*6; i++ ) {
    fputc( '=', out );
  }
  fputc( '\n', out );
  for ( i = 0; i < size; i++ ) {
    fprintf( out, "%02d-%02d ", i, i );
  }
  fputc( '\n', out );
  return 0;
}

int vshistogram( FILE *out, int a[ ], int size, char *name[ ] ) {
  int i, j = 0;
  for ( i = 1; i < size; i++ ) {
    if ( a[ j ] < a[ i ] ) {
      j = i;
    }
  }
  int cutoff = a[ j ]; /* max value of a[ ] */
  while ( cutoff > 0 ) {
    for ( i = 0; i < size; i++ ) {
      if ( cutoff == a[ i ] ) {
	fprintf( out, "  *  " );
	a[ i ]--;
      } else {
	fprintf( out, "     " );
      }
      fputc( ' ', out );
    }
    fputc( '\n', out );
    cutoff--;
  }
  for ( i = 0; i < size*6; i++ ) {
    fputc( '=', out );
  }
  fputc( '\n', out );
  for ( i = 0; i < size; i++ ) {
    fprintf( out, "%5s", name[ i ] );
    fputc( ' ', out );
  }
  fputc( '\n', out );
  return 0;
}


  
