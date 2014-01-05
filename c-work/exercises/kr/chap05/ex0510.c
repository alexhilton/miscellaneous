/**
 * ex0510.c
 * command line arguments version of Reverse Polish Calculator.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 128
static double stack[ STACK_SIZE ];
static int size = 0;
#define NUMBER 'n'
/* implementation of stack */
static void push( double a );
static double pop();
static char getop( char *str );

/* main program */
int main( int argc, char *argv[] ) {
  double op2;
  char ch;
  while ( --argc > 0 ) {
    ch = getop( *++argv );
    switch ( ch ) {
    case NUMBER:
      push( atof( *argv ) );
      break;
    case '+':
      push( pop() + pop() );
      break;
    case '-':
      op2  = pop();
      push( pop() - op2 );
      break;
    case '*':
      push( pop() * pop() );
      break;
    case '/':
      op2 = pop();
      push( pop() / op2 );
      break;
    default:
      printf( "Error: unknown operator\n" );
      break;
    }
  }
  printf( "final result is: %g\n", pop() );
  return 0;
}

static void push( double a ) {
  if ( size >= STACK_SIZE ) {
    printf( "Error: stack overflowing\n" );
    return;
  }
  stack[ size++ ] = a;
}

static double pop() {
  if ( size == 0 ) {
    printf( "Error: pop from emtpy stack\n" );
    return 0;
  }
  return stack[ --size ];
}

static char getop( char *str ) {
  char ch;
  if ( strcmp( str, "+" ) == 0 ) {
    ch = '+';
  } else if ( strcmp( str, "-" ) == 0 ) {
    ch = '-';
  } else if ( strcmp( str, "*" ) == 0 ) {
    ch = '*';
  } else if ( strcmp( str, "/" ) == 0 ) {
    ch = '/';
  } else {
    /*for ( ; isdigit( *str ) && *str != '.'; str++ )
      ;
    if ( *str == '.' ) {
      for ( ; isdigit( *str ) && *str != '\0'; str++ )
        ;
    }
    if ( *str == '\0' ) {
      ch = NUMBER;
    }*/
    ch = NUMBER;
  }
  return ch;
}
