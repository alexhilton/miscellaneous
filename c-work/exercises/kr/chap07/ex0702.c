/**
 * ex0702.c
 * solution to ex0702
 */
#include <stdio.h>
#include <ctype.h>

#define MAX_LINE 128 /* max number of chars in one line */ 
#define OCT_LEN 6 /* length of an octal value */
int inc( int p, int n );

int main( int argc, char **argv ) {
  int hexal = 0;
  int octal = 1; /* by default, we use octal to print non-graphic char */
  while ( --argc && *(*++argv) == '-' ) {
    while ( *++(*argv) ) {
      switch ( *(*argv ) ) {
	case 'o':
	  octal = 1;
	  break;
	case 'h':
	  hexal = 1;
	  break;
	default:
	  break;
      }
    }
  }
  printf( "hexal %d, octal %d\n", hexal, octal );
  char ch;
  int pos;
  int step;
  pos = 0;
  while ( (ch = getchar()) != EOF ) {
    if ( isgraph( ch ) ) {
      step = 1;
      putchar( ch );
    } else {
      step = OCT_LEN;
      if ( hexal ) {
	printf( " \\%03x ", ch );
      } else {
	printf( " \\%03o ", ch );
      }
      if ( ch == '\n' ) {
	pos = 0;
	putchar( '\n' );
      }
    }
    pos = inc( pos, step );
  }
  return 0;
}

int inc( int pos, int n ) {
  if ( pos + n < MAX_LINE ) {
    return pos + n;
  } else {
    putchar( '\n' );
    return n;
  }
}
