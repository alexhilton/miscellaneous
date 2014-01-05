/*
 * ex0501.c
 * implement getint().
 */
#include <stdio.h>
#include <ctype.h>

#define SIZE 10

static char getch( void );
static void ungetch( char ch );
static int getint( int *n );

/* main program */
int main( int argc, char **argv ) {
  int n, array[ SIZE ];
  for ( n = 0; n < SIZE && getint( &array[n] ) != EOF; n++ )
    ;
  int i;
  for ( i = 0; i < n; i++ ) {
    printf( "integer is : %d\n", array[ i ] );
  }
  return 0;
}

static int getint( int *n ) {
  int sign;
  char ch, tch;
  while ( isspace( ch = getch()) )
    ;
  if ( !isdigit( ch ) && ch != EOF && ch != '+' && ch != '-' ) {
    ungetch( ch );
    return 0;
  }

  sign = ( ch == '-' ) ? -1 : 1;
  if ( ch == '+' || ch == '-' ) {
    if ( !isdigit( tch = getch() ) ) {
      if ( tch != EOF ) {
	ungetch( tch );
      }
      ungetch( ch );
      return ch;
    } else {
      ch = tch;
    }
  }
  for ( *n = 0; isdigit(ch); ch = getch() ) {
    *n = 10 * *n + (ch - '0');
  }
  *n *= sign;
  if ( ch != EOF ) {
    return ch;
  }
  return ch;
}

static char buffer[ SIZE ];
static int bufp = 0;

static char getch( void ) {
  return ( bufp > 0 ) ? buffer[ bufp ] : getchar();
}

static void ungetch( char ch ) {
  if ( bufp >= SIZE ) {
    printf( "pushing back so many characters\n" );
  } else {
    buffer[ bufp++ ] = ch;
  }
}
