/*
 * ex0122.c
 *
 * A program to fold (wrap) long input line into two or more shorter
 * lines after the last nonblank character that occurs before
 * the n-th column of input.
 */
#include <stdio.h>

#define MAX_COL 40 /* maximum column of input */
#define TABINC 8 /* tab increment size */

char line[ MAX_COL ]; /* input line */

static int exptab( FILE *out, int pos ); /* expand tab into blanks */
static int findblnk( int pos ); /* find blank's position */
static int newpos( int pos ); /* re-arrange line with new position */
static void printline( FILE *out, int pos ); /* print line until pos column */

/* fold long input line into two or more shorter lines */
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

  char ch; /* current chara */
  int pos; /* current position */

  pos = 0;
  while ( ( ch = fgetc( in ) ) != EOF ) {
    line[ pos ] = ch; /* store current char */
    if ( ch == '\t' ) { /* deal with tab when meeting it */
      pos = exptab( out, pos );
    } else if ( ch == '\n' ) { 
      /* reach newline, print this line and start a new line */
      printline( out, pos );
      pos = 0;
    } else if ( ++pos >= MAX_COL ) {
      /* or exceeds specified columns, need to be folded or wrapped */
      /* use findblnk finds the last blank in the line */
      pos = findblnk( pos );
      /* then print the wrapped line */
      printline( out, pos );
      /* and re-arrange the line */
      pos = newpos( pos );
    }
  }
  fclose( in );
  fclose( out );

  return 0;
}

/*
 * Function: printline
 *
 * print line until pos column
 */
static void printline( FILE *out, int pos ) {
  int i;
  /* print until pos */
  for ( i = 0; i < pos; i++ ) {
    fputc( line[ i ], out );
  }
  if ( pos > 0 ) { /* any char printed ? */
    fputc( '\n', out );
  }
}

/*
 * Function: exptab
 *
 * expand tab into blanks 
 * Pre-condition: when line[ pos ] is '\t'(tab), call the 
 * routine.
 */
static int exptab( FILE *out, int pos ) {
  line[ pos ] = ' '; /* tab is at least one blanks */
  /* fill blanks until MAX_COL or next tab stop reached */
  for ( ++pos; pos < MAX_COL && pos % TABINC != 0; pos++ ) {
    line[ pos ] = ' ';
  }

  if ( pos < MAX_COL ) { /* there are spaces left in current line */
    return pos;
  } else {
    printline( out, pos );
    return 0; /* reset current position */
  }
}

/*
 * Function: findblnk
 *
 * find blank's position
 * return the position following the blank, i.e. line[ pos-1 ] is ' '
 * while line[ pos ] is non-blank.
 */
static int findblnk( int pos ) {
  while ( pos > 0 && line[ pos ] != ' ' ) {
    pos--;
  }
  if ( pos == 0 ) { /* no blanks in the line ? */
    return MAX_COL;
  } else { /* at least one blank */
    return pos+1; /* position after the blank */
  }
}

/*
 * Function: newpos
 *
 * re-arrange line with new position
 * i.e. move the char blocks back into begining of line[ ]
 */
static int newpos( int pos ) {
  int i, j;
  if ( pos <= 0 || pos >= MAX_COL ) {
    return 0; /* nothing to be re-arranged */
  } else {
    i = 0;
    for ( j = pos; j < MAX_COL; j++ ) {
      line[ i ] = line[ j ];
      i++;
    }
    return i; /* new position in line */
  }
}
