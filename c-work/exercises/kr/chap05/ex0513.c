/**
 * ex0513.c
 * implement tail utility with the option -n, default is 10 
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 50
#define MAXLEN 100 /* max length of any input line */
static char *lineptr[ MAXLINE ];
static char *myalloc( int size );
static int getline( char line[], int limit );
static int readlines( char *lineptr[], int nlines );
static void writelines( char *lineptr[], int nlines, int number );
static int strcpy( char *str1, char *str2 );

/* main program */
int main( int argc, char *argv[] ) {
  int nlines;
  int number = 10; // default trailing 10 lines

  if ( argc > 1 && *(*++argv)++ == '-' ) {
    number = atoi( *argv );
  }
  if ( (nlines = readlines( lineptr, MAXLINE )) >= 0 ) {
    printf( "+++++++++++++++++++++tailing %d lines++++++++++++++++=\n", number );
    if ( number > nlines ) {
      number = nlines;
    }
    writelines( lineptr, nlines, number );
    return 0;
  } else {
    printf( "input too big to store\n" );
    return 0;
  }
}

/* readlines: read input lines */
static int readlines( char *lineptr[], int maxlines ) {
  int len, nlines;
  char line[ MAXLEN ], *p;
  nlines = 0;
  while ( (len = getline( line, MAXLEN )) > 0 ) {
    if ( nlines >= maxlines || (p = myalloc( len+1 )) == NULL ) {
      return -1;
    } else {
      strcpy( p, line );
      lineptr[ nlines++ ] = p;
    }
  }
  return nlines;
}

/* writelines: write output liens */
static void writelines( char *lineptr[], int nlines, int number ) {
  int i;
  for ( i = nlines-number; i < nlines; i++ ) {
    printf( "%s\n", lineptr[ i ] );
  }
}

/* strcpy: copy content str2 into str1 */
static int strcpy( char *str1, char *str2 ) {
  while ( *str1++ = *str2++ )
    ;
  return 0;
}
/* some type definitions for alloc */
#define ALLOC_SIZE 10000
static char allocbuf[ ALLOC_SIZE ];
static char *allocp = allocbuf;

static char *myalloc( int len ) {
  if ( allocbuf + ALLOC_SIZE - allocp >= len ) {
    allocp += len;
    return allocp - len;
  } 
  return NULL;
}

static void afree( char *p ) {
  if ( p >= allocbuf && p < allocbuf + ALLOC_SIZE ) {
    allocp = p;
  }
}

static int getline( char *line, int len ) {
  char ch;
  int i;
  i = 0;
  while ( i < len && (ch = getchar()) != EOF && ch != '\n' ) {
    line[ i++ ] = ch;
  }
  if ( ch == '\n' ) {
    line[ i ] = '\0';
  }
  return i;
}
