/**
 * ex0511.c
 * entab and detab extended version.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAB 8
#define MAX_SIZE 1024
static int getline( char *line, int limit );
static void detab( char *line, int len );
static void entab( char *line, int len );
static void printline( char *line );

/* main program */
int main( int argc, char **argv ) {
  char line[ MAX_SIZE ];
  char before[ MAX_SIZE ];

  int len;
  printf( "testing for detab and entab, first detab, then entab\n"
	  "input a line with tabs:\n" );
  len = getline( line, MAX_SIZE );
  printf( "the string you input just now is:\n'%s'\n", line );
  printline( line );
  strcpy( before, line );
  detab( line, len );
  printf( "after detabing is:\n'%s'\n", line );
  printline( line );
  entab( line, len );
  printf( "after converting, the string is:\n'%s'\n", line );
  printline( line );
  printf( "testing result is: %d\n", strcmp( before, line ) );
  return 0;
}

static int getline( char *line, int limit ) {
  char ch;
  int len = 0;
  while ( len < limit && (ch = getchar()) != EOF && ch != '\n' ) {
    line[ len++ ] = ch;
  }
  if ( ch == '\n' ) {
    line[ len ] = '\0';
  }
  return len;
}

static void detab( char *line, int len ) {
  int i = 0, j = 0;
  int nt = 0;
  int m = 0;
  int stop = 0;
  char *copy = (char *) malloc( len + 1 );
  strcpy( copy, line );
  while ( copy[ i ] != '\0' ) {
    if ( copy[ i ] == '\t' ) {
      nt = 0;
      while ( copy[ i ] == '\t' ) {
   	nt++;
	i++;
      }
      stop = j + TAB - j % TAB;
      if ( j < stop - 1 ) {
	nt--;
      }
      for ( ; j < stop - 1; j++ ) {
	line[ j ] = ' ';
      }
      for ( m = 0; m < nt * TAB; m++ ) {
	line[ j++ ] = ' ';
      }
    } else {
      line[ j++ ] = copy[ i++ ];
    }
  }
  line[ j ] = '\0';
}

static void entab( char *line, int len ) {
  int i, m = 0, j, k, stop, nt = 0, nb = 0;
  i = 0;
  j = 0;
  char *copy = (char *) malloc( len + 1 );
  strcpy( copy, line );
  while ( copy[ i ] != '\0' ) {
    if ( copy[ i ] == ' ' ) {
      k = i;
      while ( copy[ k++ ] == ' ' )
	;
      nt = 0;
      nb = 0;
      stop = i + TAB - i % TAB;
      if ( k < stop ) {
	nb = ( k - i ) % TAB;
	for ( m = 0; m < nb-1; m++ ) {
	  line[ j++ ] = ' ';
	}
      } else {
	while ( stop <= k ) {
	  nt++;
	  stop += TAB;
	}	
	for ( m = 0; m < nt; m++ ) {
	  line[ j++ ] = '\t';
	}
	for ( m = 0; m < k-stop+TAB; m++ ) {
	  line[ j++ ] = ' ';
	}
      }
      i = --k;
    } else {
      line[ j++ ] = copy[ i++ ];
    }
  }
  line[ j ] = '\0';
}

static void printline( char *line ) {
  for ( ; *line != '\0'; line++ ) {
    if ( *line == '\t' ) {
      printf( "\\t, " );
    } else {
      printf( "'%c', ", *line );
    }
  }
  printf( "\n" );
}
