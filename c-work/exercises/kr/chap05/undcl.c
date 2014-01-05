/**
 * File: $Header$
 * Author: $Author$
 * Name: $Name$
 * Date: $Date$
 * Email: alexhilton@nefw.com
 *
 * RCS ID: $Id$
 * Revision: $Revision$
 * $Log$
 *
 * Descritption:
 *
 * TODO:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/* Macros */
#define MAX_TOKEN 100

/* Typedef and Data structures */
enum { NAME, PARENS, BRACKETS };

/* External function prototypes */
/**
 * @Function: 
 * @Param:
 * @Param:
 * @Return:
 * @Description:
 * @Pre-condition:
 * @Post-condition:
 * @TODO:
 */

/* External variables */

/* Private function prototypes */
/**
 * @Function: void dcl( void );
 * @Param:
 * @Return:
 * @Description: parse a delclarator
 * @Pre-condition:
 * @Post-condition:
 * @TODO:
 */
static void dcl( void );

/**
 * @Function: void dirdcl( void );
 * @Param:
 * @Return:
 * @Description: parse a direct delclarator
 * @Pre-condition:
 * @Post-condition:
 * @TODO:
 */
static void dirdcl( void );

/**
 * @Function: char gettoken( void );
 * @Param:
 * @Return: return the token type
 * @Description: read the next token.
 * @Pre-condition:
 * @Post-condition:
 * @TODO:
 */
static char gettoken( void );

/**
 * @Function: char getch( void );
 * @Param:
 * @Return: return the next char from standard input 
 * @Description: read the next char on input stream.
 * @Pre-condition:
 * @Post-condition:
 * @TODO:
 */
static char getch( void );

/**
 * @Function: void ungetch( char ch );
 * @Param:
 * @Return: 
 * @Description: push back a char to input stream
 * @Pre-condition:
 * @Post-condition:
 * @TODO:
 */
static void ungetch( char ch );

/* Private global variables */
static char tokentype;  /* type of last token */
static char token[ MAX_TOKEN ]; /* last token string */
static char name[ MAX_TOKEN ]; /* indentifier name */
static char datatype[ MAX_TOKEN ]; /* data type = char, int, etc */
static char out[ 1000 ]; /* output string */
static char buf[ MAX_TOKEN ];
static int bufp = 0;

/* Main program */
/**
 * convert declaration into words
 */
int main( int argc, char **argv ) {
  int type;
  char tmp[ MAX_TOKEN ];

  while ( gettoken() != EOF ) { /* 1st token on line */
    strcpy( out, token );
    while ( (type = gettoken()) != '\n' ) {
      if ( type == PARENS || type == BRACKETS ) {
	strcat( out, token );
      } else if ( type == '*' ) {
	sprintf( tmp, "(*%s)", out );
        strcpy( out, tmp );
      } else if ( type == NAME ) {
	sprintf( tmp, "%s %s", token, out );
	strcpy( out, tmp );
      } else {
	printf( "invalid input at %s\n", token );
      }
    }
    printf( "%s: %s %s\n", name, out, datatype );
  }
  return 0;
}


/* External function definitions */

/* Private funtion definitions */
static void dcl( void ) {
  int ns;
  for ( ns = 0; gettoken() == '*'; ) {
    ns++;
  }
  dirdcl();
  while ( ns-- > 0 ) {
    strcat( out, " pointer to" );
  }
}

static void dirdcl( void ) {
  char type;

  if ( tokentype == '(' ) {
    dcl();
    if ( tokentype != ')' ) {
      printf( "error: missing ')'\n" );
    }
  } else if ( tokentype == NAME ) {
    strcpy( name, token );
  } else {
    printf( "error: expected name or (dcl)\n" );
  }
  while ( (type = gettoken()) == PARENS || type == BRACKETS ) {
    if ( type == PARENS ) {
      strcat( out, " function returning" );
    } else {
      strcat( out, " array" );
      strcat( out, token );
      strcat( out, " of" );
    }
  }
}

static char gettoken( void ) {
  char ch;
  char *p = token;

  while ( (ch = getch()) == ' ' || ch == '\t' )
    ;
  if ( ch == '(' ) {
    if ( (ch = getch()) == ')' ) {
      strcpy( token, "()" );
      return tokentype = PARENS;
    } else {
      ungetch( ch );
      return tokentype = '(';
    }
  } else if ( ch == '[' ) {
    for ( *p++ = ch; (*p++ = getch()) != ']'; )
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if ( isalpha( ch ) ) {
    for ( *p++ = ch; isalnum( ch = getch() ); ) {
      *p++ = ch;
    }
    *p = '\0';
    ungetch( ch );
    return tokentype = NAME;
  } else {
    return tokentype = ch;
  }
}

static char getch( void ) {
  if ( bufp > 0 ) {
    return buf[ --bufp ];
  }
  return getchar();
}

static void ungetch( char ch ) {
  if ( bufp >= MAX_TOKEN ) {
    printf( "Error: pushing back so many chars\n" );
    return;
  }
  buf[ bufp++ ] = ch;
}

/* End of $Source$ */
