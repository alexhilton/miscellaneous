/*
 * ex0116.c
 *
 * revise the main routine of the longline.c program so it will correctly
 * print the length of arbitrarily long input lines, and as much as
 * possible of the text.
 */
#include <stdio.h>

#define SIZE 128 

static int getline( FILE *in, char buf[ ], int lim );
static int copy( char from[ ], char to[ ] );

int main( int argc, char *argv[ ] ) {
  int len;
  char longest[ SIZE ];
  char line[ SIZE ];
  int max = 0;

  FILE *in;
  in = fopen( "input.dat", "r" );
  if ( in == NULL ) {
    perror( "input.dat" );
    return 1;
  }

  while ( (len = getline( in, line, SIZE )) > 0 ) {
    printf( "%d:%s\n", len, line );
    if ( max < len ) {
      max = len;
      copy( longest, line );
    }
  }
  if ( max > 0 ) {
    printf( "max line is:\n%s\n", longest );
  }
  fclose( in );
  return 0;
}

int getline( FILE *in, char buf[ ], int lim ) {
  int i;
  char ch;
  i = 0;
  for ( ; i < lim && (ch = fgetc( in )) != EOF; i++ ) {
    if ( ch == '\n' ) {
      buf[ i ] = '\0';
      return i;
    } else {
      buf[ i ] = ch;
    }
  }
  return i;
}

int copy( char to[ ], char from[ ] ) {
  int i;
  for ( i = 0; from[ i ] != '\0'; i++ ) {
    to[ i ] = from[ i ];
  }
  if ( from[ i ] != '\0' ) {
    return 1;
  }
  return 0;
}
