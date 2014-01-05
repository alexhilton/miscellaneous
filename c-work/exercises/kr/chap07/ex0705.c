/*
 * ex0705.c
 * Reverse Polish calculator.
 * with scanf
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_OP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

/**
 * Stack implementation
 */
static int getop();
static void push( double elem );
static double pop( void );

/* main program */
int main( int argc, char **argv ) {
  int type;
  double op2, val;

  while ( (type = getop()) != EOF ) {
    switch ( type ) {
    case NUMBER:
      scanf( "%lf", &val );
      push( val );
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
      printf( "Error: unknown command \n" );
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
static char buf[ BUF_SIZE ]; /* buffer for ungetch */
static int bufp = 0; /* next free position in buf */

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

/* getop: get next operator or numeric operands */
static int getop() {
  char ch;
  /* skip whitespaces */
  while ( (ch = getch()) == ' ' || ch == '\t' )
    ;
  /* when ch is not a number, return value */
  /* now ch gotta be an operator */
  if ( !isdigit( ch ) && ch != '.' ) {
    return ch;
  }

  if ( ch != EOF ) {
    ungetc( ch, stdin );
  }
  return NUMBER;
}



/* get a (possibly pushed back) character */
static int getch( void ) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}
