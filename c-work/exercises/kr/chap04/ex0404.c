/*
 * ex0404.c
 * extension to Reverse Polish calculator.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_OP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

/**
 * Stack implementation
 */
static char getop( char str[] );
static void push( double elem );
static double pop( void );
static void printTop();
static void swapTop();
static void clearStack();

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
    case '%':
      op2 = pop();
      double op1 = pop();
      if ( op2 != 0.0 ) {
	push( fmod( op1, op2 ) );
      } else {
	printf( "Error: divided by zeros\n" );
      }
   case 'p':
      printTop();
      break;
   case 'c':
      clearStack();
      break;
   case 's':
      swapTop();
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

static void printTop() {
  if ( sp > 0 ) {
    printf( "%g\n", val[ sp - 1 ] );
  } else {
    printf( "stack is empty\n" );
  }
}

static void swapTop() {
  if ( sp > 1 ) {
    val[ sp - 1 ] -= val[ sp - 2 ];
    val[ sp - 2 ] += val[ sp - 1 ];
    val[ sp - 1 ] = val[ sp - 2 ] - val[ sp - 1 ];
  }
}

static void clearStack() {
  sp = 0;
}

static int getch( void );
static void ungetch( char ch );


/* getop: get next operator or numeric operands */
static char getop( char str[] ) {
  /* for testing and debugging */
  int i;
  char ch;
  /* skip whitespaces */
  while ( (str[ 0 ] = ch = getch()) == ' ' || ch == '\t' )
    ;
  /* str[ 1 ] = '\0'; */
  /* when ch is not a number, return value */
  /* now ch gotta be one of + / * and % */
  /* for -, we have to deal sepcially, because it is confusing */
  if ( !isdigit( ch ) && ch != '.' && ch != '-' ) {
    return ch;
  }

  i = 0;
  if ( ch == '-' ) {
    if ( isdigit( ch = getch() ) ) {
      /* negative number */
      ungetch( ch );
      str[ 0 ] = '-';
    } else {
      ungetch( ch );
      return '-'; /* minus operator */
    }
  }
  if ( isdigit( ch ) && ch != '.' ) {
    while ( isdigit( str[++i] = ch = getch() ) )
      ;
  } else {
    /* commands */
    return ch;
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

#define BUF_SIZE 100
static char buf[ BUF_SIZE ]; /* buffer for ungetch */
static int bufp = 0; /* next free position in buf */

/* get a (possibly pushed back) character */
static int getch( void ) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
static void ungetch( char ch ) {
  if ( bufp >= BUF_SIZE ) {
    printf( "ungetch: too many characters\n" );
  } else {
    buf[bufp++] = ch;
  }
}
