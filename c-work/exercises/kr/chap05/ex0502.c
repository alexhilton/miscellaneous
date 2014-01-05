/*
 * ex0502.c
 * implement getfloat().
 */
#include <stdio.h>
#include <ctype.h>

#define SIZE 10

static char getch( void );
static void ungetch( char ch );
static int getfloat( float *x );

/* main program */
int main( int argc, char **argv ) {
  int n;
  float array[ SIZE ];
  for ( n = 0; n < SIZE && getfloat( &array[n] ) != EOF; n++ )
    ;
  int i;
  for ( i = 0; i < n; i++ ) {
    printf( "floating-point number is : %g\n", array[ i ] );
  }
  return 0;
}

static int getfloat( float *x ) {
  int sign;
  char ch;
  float base;
  while ( isspace( ch = getch()) )
    ;
  if ( !isdigit( ch ) && ch != EOF && ch != '+' && ch != '-' ) {
    ungetch( ch );
    return 0;
  }

  sign = ( ch == '-' ) ? -1 : 1;
  if ( ch == '+' || ch == '-' ) {
    ch = getch();
  }
  for ( *x = 0; isdigit(ch); ch = getch() ) {
    *x = 10 * *x + (ch - '0');
  }
  if ( ch == '.' ) {
    for ( base = 10.0; isdigit( ch ); ch = getch() ) {
      *x += (ch - '0') / base;
      base *= 10.0;
    }
  }
  *x *= sign;
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
