/*
 * ex0113
 *
 * this is the right version of it.
 * Print the word length distributions using horizontal histogram and
 * vertical histogram.
 * But there are some bugs that need to be modified and improved.
 * 	#1: the width and the format of index
 * 	#2: the limits of max hist and max length
 */
#include <stdio.h>

#define MAX_HIST 15 /* max length of histogram */
#define MAX_LENGTH 15 /* max length of a word */
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* print horizontal histogram */
int hhist( FILE *out, int wl[ ], int ovflow );
int vhist( FILE *out, int wl[ ], int ovflow );

int main( int argc, char *argv[ ] ) {

  char ch; /* current char */
  int i, state; /* current state: inside or outside a word */
  int wordlen; /* length of a word */
  int ovflow; /* number of words that is greater or equal to MAX_LENGTH */
  /* word length counter, recording word number of a length */
  int wlc[ MAX_LENGTH ]; 
  FILE *in, *out;

  in = fopen( "input.dat", "r" );
  out = fopen( "output.dat", "w" );
  if ( in == NULL || out == NULL ) {
    perror( "In Out" );
    return 1;
  }

  state = OUT;
  wordlen = 0;
  ovflow = 0;
  for ( i = 0; i < MAX_LENGTH; i++ ) {
    wlc[ i ] = 0;
  }

  while ( (ch = fgetc( in )) != EOF ) {
    if ( ch == ' ' || ch == '\n' || ch == '\t' ) { /* white spaces */
      state = OUT;
	if ( wordlen < MAX_LENGTH ) {
	  wlc[ wordlen ]++; /* one more word whose length is wordlen */
	} else {
	  ovflow++; /* one more word whose length is overflowing */
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

  int rc; /* return code for drawing histograms */
  rc = hhist( out, wlc, ovflow );
  rc = vhist( out, wlc, ovflow );
  if ( rc > 0 ) {
    printf( "Error occured when drawing histogram\n" );
    return 1;
  }

  fclose( in );
  fclose( out );
  return 0;
}

int hhist( FILE *out, int wlc[ ], int ovflow ) {
  int maxvalue = 0;
  int i, j = 1;
  for ( i = 2; i < MAX_LENGTH; i++ ) {
    if ( wlc[ j ] < wlc[ i ] ) {
      j = i;
    }
  }
  maxvalue = wlc[ j ];
  int len; /* length of a bar */
  int tmp = MAX_HIST / maxvalue;

  /* drawing the histogram */
  for ( i = 1; i < MAX_LENGTH; i++ ) {
    /* print index */
    fprintf( out, "%02d-%02d|", i, wlc[ i ] );
    /* print the histogram or the bar */
    if ( wlc[ i ] > 0 ) {
      len = tmp * wlc[ i ];
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
  if ( ovflow > 0 ) {
    fprintf( out, "overflow |" );
    len = ovflow * tmp;
    while ( len > 0 ) {
      fputc( '*', out );
      len--;
    }
    fputc( '\n', out );
  }
  return 0;
}

int vhist( FILE *out, int wlc[ ], int ovflow ) {
  int maxvalue = 0;
  int i, j = 1;
  for ( i = 2; i < MAX_LENGTH; i++ ) {
    if ( wlc[ j ] < wlc[ i ] ) {
      j = i;
    }
  }
  maxvalue = wlc[ j ];
  int tmp = MAX_HIST / maxvalue;

  /* drawing the histogram */
  for ( i = MAX_HIST; i > 0; i-- ) {
    for ( j = 1; j < MAX_LENGTH; j++ ) {
      if ( wlc[ j ] * tmp >= i ) {
	fprintf( out, "  *  " );
      } else {
	fprintf( out, "     " );
      }
    }
    fputc( '\n', out );
  }

  /* print index */
  for ( i = 1; i < MAX_LENGTH; i++ ) {
    fprintf( out, "=====" );
  }
  fputc( '\n', out );

  for ( i = 1; i < MAX_LENGTH; i++ ) {
    fprintf( out, "%02d-%02d", i, wlc[ i ] );
  }
  fputc( '\n', out );

  if ( ovflow > 0 ) {
    fprintf( out, "there are %04d words overflowing!", ovflow );
  }
  return 0;
}
