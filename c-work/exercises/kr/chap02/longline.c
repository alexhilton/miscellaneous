/*
 * longline.c
 *
 * page 29
 * reads a set of text lines and prints the longest..
 */
#include <stdio.h>

#define MAX_LINE 1000 /* maximum input line size */

int getline( FILE *in, char line[ ], int maxline );
void copy( char to[ ], char from[ ] );

/* print longest input line */
int main( int argc, char *argv[ ] ) {
  int len; /* current line length */
  int max; /* maximum length seen so far */
  char line[ MAX_LINE ]; /* current input line */
  char longest[ MAX_LINE ]; /* longest line saved here */
  FILE *in;

  if ( argc != 2 ) {
    printf( "Missing input files\n" );
    return 1;
  }
  if ( (in = fopen( argv[ 1 ], "r" )) == NULL ) {
    perror( argv[ 1 ] );
    return 1;
  }
  max = 0;
  while ( (len = getline( in, line, MAX_LINE )) > 0 ) {
    if ( len > max ) {
      max = len;
      copy( longest, line );
    }
  }
  if ( max > 0 ) {
    printf( "%d:%s", max, longest );
  }
  return 0;
}

/* getline: read a line into s, return length */
int getline( FILE *in, char s[ ], int lim ) {
  int c, i;
  for ( i = 0; i<lim-1 && (c = fgetc(in))!=EOF && c!='\n'; i++ ) {
    s[ i ] = c;
  }
  if ( c == '\n' ) {
    s[ i ] = c;
    i++;
  }
  s[ i ] = '\0';
  return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy( char to[ ], char from[ ] ) {
  int i;
  i = 0;
  while ( (to[ i ] = from[ i ]) != '\0' ) {
    i++;
  }
}
