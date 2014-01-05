/**
 * ex0516.c
 * sort on numeric or strings.
 * add option -r to sort in decreasing order.
 * add option -f to ignore case.
 * add option -d to compare only on letters, numbers and blanks.
 */
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXLINE 50
#define MAXLEN 100 /* max length of any input line */
static char *lineptr[ MAXLINE ];
static char *alloc( int size );
static void swap( char *v[], int i, int j );
static int getline( char line[], int limit );
static int readlines( char *lineptr[], int nlines );
static void writelines( char *lineptr[], int nlines );

static void myqsort( char *lineptr[], int left, int right, int (*comp)( char *a, char *b ) );
static int ncmp( char *a, char *b );
static int strcmp( char *a, char *b );
static int strcpy( char *a, char *b );
static int myisalpha( char ch );
static char mytolower( char ch );
static int myisdigit( char ch );
static int myisspace( char ch );

/* for option flags */
static int reverse = 1; // 1 -- ascending; -1 -- descending 
static int fold = 0; // 1 -- fold; 0 -- not fold
static int directory = 0; // 0 -- not; 1 -- directory

/* main program */
int main( int argc, char *argv[] ) {
  int nlines;
  int numeric = 0; /* 1 -- numeric; 0 -- string */
  char ch;

  while ( --argc > 0 && (*++argv)[0] == '-' ) {
    while ( (ch = *(*argv)++) != '\0' ) {
      switch ( ch ) {
      case 'n':
	numeric = 1;
	break;
      case 'r':
	reverse = -1;
	break;
      case 'f':
	fold = 1;
	break;
      case 'd':
	directory = 1;
	break;
      default:
	break;
      }
    }
  }

  printf( "numeric is %d, reverse is %d, fold is %d, directory is %d\n", numeric, reverse, fold, directory );
  if ( (nlines = readlines( lineptr, MAXLINE )) >= 0 ) {
    //printf( "+++++++++++++++++++++before sorting++++++++++++++++=\n" );
    //writelines( lineptr, nlines );
    myqsort( (char **) lineptr, 0, nlines-1,
	   (int (*)(char *, char *))(numeric ? ncmp : strcmp) );
    printf( "+++++++++++++++++++++after sorting++++++++++++++++=\n" );
    writelines( lineptr, nlines );
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
    //printf( "=========line is: '%s'\n", line );
    if ( nlines >= maxlines || (p = alloc( len+1 )) == NULL ) {
      return -1;
    } else {
      strcpy( p, line );
     // printf( "########p is: '%s'\n", p );
     // p[ len ] = '\0';
      lineptr[ nlines++ ] = p;
      //printf( "########lineptr[ %d ] is: '%s'\n", nlines-1, lineptr[ nlines-1 ] );
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

/* myqsort: sort v[left] ... v[right] inot assending order */
static void myqsort( char *v[], int left, int right, int (*comp)( char *a, char *b ) ) {
  int i, last;

  if ( left >= right ) {
    return;
  }
  swap( v, left, (left + right) / 2 );
  last = left;
  for ( i = left+1; i <= right; i++ ) {
    int cmp = (*comp)( v[ i ], v[ left ] );
    if ( cmp * reverse < 0 ) {
      swap( v, ++last, i );
    }
  }
  swap( v, left, last );
  myqsort( v, left, last-1, comp );
  myqsort( v, last+1, right, comp );
}

static void swap( char *v[], int i, int j ) {
  char *temp;
  temp = v[ i ];
  v[ i ] = v[ j ];
  v[ j ] = temp;
}

static int ncmp( char *a, char *b ) {
  double v1, v2;
  v1 = atof( a );
  v2 = atof( b );
  if ( v1 < v2 ) {
    return -1;
  } else if ( v1 > v2 ) {
    return 1;
  } else {
    return 0;
  }
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
  while ( i < len && (ch = getchar()) != EOF && ch != '\n' ) {
    line[ i++ ] = ch;
  }
  if ( ch == '\n' ) {
    line[ i ] = '\0';
  }
  return i;
}

static int strcmp( char *a, char *b ) {
  char p = *a, q = *b;
  while ( 1 ) {
    if ( directory ) {
      while ( !myisdigit(p) && !myisalpha(p) && !myisspace(p) ) {
	p = *a++;
      }
      while ( !myisdigit(q) && !myisalpha(q) && !myisspace(q) ) {
	q = *b++;
      }
    } 
    if ( fold ) {
      p = mytolower( *a );
      q = mytolower( *b );
    } else {
      p = *a;
      q = *b;
    }
    if ( p == q && p == '\0' ) {
      return 0;
    } else if ( p != q ) {
      break;
    }
    a++;
    b++;
  }
  return p - q;
}


static int strcpy( char *a, char *b ) {
  while ( *a++ = *b++ )
    ;
  return 0;
}

static int myisalpha( char ch ) {
  return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

static char mytolower( char ch ) {
  if ( myisalpha( ch ) ) {
    if ( ch >= 'A' && ch <= 'Z' ) {
      ch += 'a' - 'A';
    }
  }
  return ch;
}

static int myisdigit( char ch ) {
  return (ch >= '0' && ch <= '9');
}

static int myisspace( char ch ) {
  return (ch == ' ' || ch == '\t' || ch == '\n');
}
