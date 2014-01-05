/*
 * ex0410.c
 * Reverse Polish calculator.
 * Using getline() instead of get a char from input stream.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_OP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

/**
 * Stack implementation
 */
static int getop( char str[] );
static void push( double elem );
static double pop( void );

/* main program */
int main( int argc, char **argv ) {
  int type;
  double op2;
  char str[ MAX_OP ];

  while ( (type = getop(str)) != EOF ) {
    switch ( type ) {
    case NUMBER:
      push( atof( str ) );
      break;
    case '+':
      push( pop() + pop() );
      break;
    case '*':
      push( pop() * pop() );
      break;
    case '-':
      op2 = pop();
      push( pop() - op2 );
      break;
    case '/':
      op2 = pop();
      if ( op2 != 0.0 ) {
	push( pop() / op2 );
      } else {
	printf( "Error: divided by zeros\n" );
      }
      break;
    case '\n':
      printf( "\t%.8g\n", pop() );
      break;
    default:
      printf( "Error: unknown command %s\n", str );
      break;
    }
  }
  return 0;
}

/**
 * A stack implementation
 */
#define MAX_VAL 100 /* maximum depth of val stack */

static int sp = 0; /* next free stack position */
static double val[ MAX_VAL ]; /* value stack */


/* push: push f onto value stack */
static void push( double f ) {
  if ( sp < MAX_VAL ) {
    val[ sp++ ] = f;
  } else {
    printf( "Error: stack full, can't push %g\n", f );
  }

}

/* pop: pop and return top value from stack */
/* 0.0 implies reach bottom of stack */
static double pop( void ) {
  if ( sp > 0 ) {
    return val[ --sp ];
  } else {
    printf( "Error: pop from empty stack\n" );
    return 0.0;
  }
}

static int getline( void );
#define BUF_SIZE 128
static char buf[ BUF_SIZE ];
static int bufp = 0;
static int buflen = 0;

/* getop: get next operator or numeric operands */
static int getop( char str[] ) {
  if ( buflen == bufp ) {
    buflen = getline();
    bufp = 0;
    if ( buflen == EOF ) {
      return EOF;
    }
  }
  /* for testing and debugging */
  /* printf( "\t: buffer is: '%s'\n", buf ); */
  int i;
  char ch;
  /* skip whitespaces */
  while ( bufp < buflen && ((str[0] = ch = buf[ bufp++ ]) == ' ' || ch == '\t') )
    ;
  str[ 1 ] = '\0';
  /* when ch is not a number, return value */
  /* now ch gotta be an operator */
  if ( !isdigit( ch ) && ch != '.' ) {
    return ch;
  }
  i = 0;
  /* get integer part */
  if ( isdigit( ch ) && ch != '.' ) {
    while ( bufp < buflen && isdigit( str[++i] = ch = buf[ bufp++ ]) )
      ;
  } 
  /* get fraction part */
  if ( ch == '.' ) {
    while ( bufp < buflen && isdigit( str[++i] = ch = buf[ bufp++ ] ) )
      ;
  }

  str[ i ] = '\0';
  if ( ch != EOF ) {
    bufp--;
  }
  return NUMBER;
}


static int getline( void ) {
  if ( fgets( buf, sizeof( buf ), stdin ) == NULL ) {
    return EOF;
  }
  
  return strlen( buf );
}
