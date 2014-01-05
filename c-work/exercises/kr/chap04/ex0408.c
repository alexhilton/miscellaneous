/*
 * ex0408.c
 * Reverse Polish calculator.
 * Modify getch() and ungetch() based on the assumption that there will be no more than one character.
 */
#include <stdio.h>
#include <stdlib.h>
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

#define BUF_SIZE 100
static char buf; /* buffer for ungetch */
static int buffered = 0; /* buffered or not */

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

static int getch( void );
static void ungetch( char ch );

/* getop: get next operator or numeric operands */
static int getop( char str[] ) {
  /* for testing and debugging */
  /* printf( "\t: buffer is: '%s'\n", buf ); */
  int i;
  char ch;
  /* skip whitespaces */
  while ( (str[0] = ch = getch()) == ' ' || ch == '\t' )
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
    while ( isdigit( str[++i] = ch = getch() ) )
      ;
  } 
  /* get fraction part */
  if ( ch == '.' ) {
    while ( isdigit( str[++i] = ch = getch() ) )
      ;
  }

  str[ i ] = '\0';
  if ( ch != EOF ) {
    ungetch( ch );
  }
  return NUMBER;
}



/* get a (possibly pushed back) character */
static int getch( void ) {
  if ( buffered ) {
    buffered = 0;
    return buf;
  } else {
    buffered = 0;
    return getchar();
  }
}

/* push character back on input */
static void ungetch( char ch ) {
  if ( buffered ) {
    printf( "ungetch: too many characters\n" );
  } else {
    buf = ch;
    buffered = 1;
  }
}
