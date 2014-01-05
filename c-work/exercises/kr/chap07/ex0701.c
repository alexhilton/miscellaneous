/**
 * ex0701.c
 */
#include <stdio.h>

static int strcmp( char *a, char *b );
static char mytolower( char ch );
static char mytoupper( char ch );

int main( int argc, char **argv ) {
  char ch;
  if ( strcmp( *argv, "ex0701" ) == 0 ) {
    while ( (ch = getchar()) != EOF ) {
      putchar( mytolower( ch ) );
    }
  } else {
    while ( (ch = getchar()) != EOF ) {
      putchar( mytoupper( ch ) );
    }
  }
  return 0;
}

static int strcmp( char *str1, char *str2 ) {
  while ( *str1 == *str2 ) {
    if ( *str1 == '\0' ) {
      return 0;
    }
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

static char mytolower( char ch ) {
  if ( ch >= 'A' && ch <= 'Z' ) {
    return ch + 'a' - 'A';
  }
  return ch;
}

static char mytoupper( char ch ) {
  if ( ch >= 'a' && ch <= 'z' ) {
    return ch - 'a' + 'A';
  }
  return ch;
}
