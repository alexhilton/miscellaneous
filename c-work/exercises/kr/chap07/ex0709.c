/**
 * ex0709.c
 * solution to ex0709
 */
#include <stdio.h>
#include <ctype.h>

/* time saving implementation */
#define timeisupper( ch ) ( (ch) >= 'A' && (ch) <= 'Z' )

/* space saving implementation */
static int spaceisupper( char ch ) {
  return ch >= 'A' && ch <= 'Z';
}

int main( int argc, char **argv ) {
  char ch;
  while ( (ch = getchar()) != EOF ) {
    if ( timeisupper( ch  ) ) {
      putchar( tolower( ch ) );
    }
    if ( spaceisupper( ch ) ) {
      putchar( toupper( ch ) );
    }
  }
  putchar( '\n' );
  return 0;
}
