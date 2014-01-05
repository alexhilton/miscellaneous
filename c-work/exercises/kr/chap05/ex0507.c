/**
 * ex0507.c
 * read all the lines of input, sort them and print them in order
 */
#include <stdio.h>
#include <string.h>

#define MAX_LINES 10 /* max #lines to be stored */
#define MAXLEN 1000 /* max length of any input line */
char *lineptr[ MAX_LINES ]; /* pointers to text lines */

static int readlines( char *lineptr[], int nlines );
static void writelines( char *lineptr[], int nlines );
static void qsort( char *lineptr[], int left, int right );
static int getline( char *line, int len );
static char *alloc( int size );
static void swap( char *v[], int i, int j );

/* main program */
int main( int argc, char **argv ) {
  int nlines; /* number of input lines read */
  /* allocate memory storage spaces for lineptr */
  for ( int i = 0; i < MAX_LINES; i++ ) {
    lineptr[ i ] = alloc( MAXLEN );
  }
  printf( "input some lines of strings, we'll sort them for you...\n" );
  if ( (nlines = readlines( lineptr, MAX_LINES )) >= 0 ) {
    qsort( lineptr, 0, nlines-1 );
    printf( "the sorted assendingly are:\n" );
    writelines( lineptr, nlines );
    return 0;
  } else {
    printf( "error: input too big to sort\n" );
    return 1;
  }
}


/* readlines: read input lines */
static int readlines( char *linetr[], int maxlines ) {
  int len, nlines;
  char line[ MAXLEN ];
  nlines = 0;
  while ( (len = getline( line, MAXLEN )) > 0 ) {
    if ( nlines >= maxlines ) {
      return -1;
    } else {
      line[ len-1 ] = '\0'; /* delete newline char */
      strcpy( lineptr[ nlines++ ], line );
    }
  }
  return nlines;
}

/* writelines: write output liens */
static void writelines( char *lineptr[], int nlines ) {
  int i;
  for ( i = 0; i < nlines; i++ ) {
    printf( "%s\n", lineptr[ i ] );
  }
}

/* qsort: sort v[left] ... v[right] inot assending order */
static void qsort( char *v[], int left, int right ) {
  int i, last;

  if ( left >= right ) {
    return;
  }
  swap( v, left, (left + right) / 2 );
  last = left;
  for ( i = left+1; i <= right; i++ ) {
    if ( strcmp( v[i], v[left] ) < 0 ) {
      swap( v, ++last, i );
    }
  }
  swap( v, left, last );
  qsort( v, left, last-1 );
  qsort( v, last+1, right );
}

static void swap( char *v[], int i, int j ) {
  char *temp;
  temp = v[ i ];
  v[ i ] = v[ j ];
  v[ j ] = temp;
}

/* some type definitions for alloc */
#define ALLOC_SIZE 10000
static char allocbuf[ ALLOC_SIZE ];
static char *allocp = allocbuf;

static char *alloc( int len ) {
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
  while ( --len > 0 && (ch = getchar()) != EOF && ch != '\n' ) {
    line[ i++ ] = ch;
  }
  if ( ch == '\n' ) {
    line[ i++ ] = ch;
  }
  line[ i ] = '\0';
  return i;
}
