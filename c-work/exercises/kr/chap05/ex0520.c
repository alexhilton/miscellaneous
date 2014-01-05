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
enum { NO, YES }; /* there is no previous token */

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
 * @Function: void ungetch( char ch );
 * @Param:
 * @Return: 
 * @Description: push back a char to input stream
 * @Pre-condition:
 * @Post-condition:
 * @TODO:
 */
static int getline( char *line, int limit );

static void errmsg( char *msg ); 

static void paramdcl( void );

static int typequal( void );

/* Private global variables */
static char line[ MAX_TOKEN ]; /* the line to be intepratated. */
static int index = 0; /* the index of char in line */
static char tokentype;  /* type of last token */
static char token[ MAX_TOKEN ]; /* last token string */
static char name[ MAX_TOKEN ]; /* indentifier name */
static char datatype[ MAX_TOKEN ]; /* data type = char, int, etc */
static char out[ 1000 ]; /* output string */
static int prevtoken = NO;

/* Main program */
/**
 * convert declaration into words
 */
int main( int argc, char **argv ) {
  int len = 0;
  while ( (len = getline( line, MAX_TOKEN )) > 0 ) {
    printf( "===============================================\n" );
    printf( "++++%s+++++:\n", line );
    index = 0;
    *out = '\0';
    *name = '\0';
    *token = '\0';
    *datatype = '\0';
    dcl();
    if ( index < len ) {
      printf( "syntax error\n" );
    }
    printf( "%s: %s %s\n", name, out, datatype );
    printf( "==============================================\n" );
  }
  return 0;
}


/* External function definitions */

/* Private funtion definitions */
static void dcl( void ) {
  gettoken();
  strcpy( datatype, token );
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
      errmsg( "error: missing ')'\n" );
    }
  } else if ( tokentype == NAME ) {
    if ( *name == '\0' ) {
      strcpy( name, token );
    }
  } else {
    prevtoken = YES;
  }
  while ( (type = gettoken()) == PARENS || type == BRACKETS || type == '(' ) {
    if ( type == PARENS ) {
      strcat( out, " function returning" );
    } else if ( type == '(' ) {
      strcat( out, " function expecting" );
      paramdcl();
      strcat( out, " and returning" );
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

  if ( prevtoken == YES ) {
    prevtoken = NO;
    return tokentype;
  }
  while ( (ch = line[ index++ ]) == ' ' || ch == '\t' )
    ;
  if ( ch == '(' ) {
    if ( (ch = line[ index++ ]) == ')' ) {
      strcpy( token, "()" );
      return tokentype = PARENS;
    } else {
      index--;
      return tokentype = '(';
    }
  } else if ( ch == '[' ) {
    for ( *p++ = ch; (*p++ = line[ index++ ]) != ']'; )
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if ( isalpha( ch ) ) {
    for ( *p++ = ch; isalnum( ch = line[ index++ ] ); ) {
      *p++ = ch;
    }
    *p = '\0';
    index--;
    if ( typequal() == YES ) {
      //printf( "&&& '%s' is a qualifier\n", token );
      for ( *p++ = ch, index++; isalnum( ch = line[ index++ ] ); ) {
	*p++ = ch;
      }
      *p = '\0';
      index--;
    }
    //printf( "&&&token is: '%s'\n", token );
    return tokentype = NAME;
  } else {
    return tokentype = ch;
  }
}

static int getline( char line[], int limit ) {
  int i = 0;
  char ch;
  while ( i < limit && (ch = getchar()) != EOF && ch != '\n' ) {
    line[ i++ ] = ch;
  }
  if ( ch == '\n' ) {
    line[ i ] = '\0';
  }
  return i;
}

static void errmsg( char *msg ) {
  printf( "%s\n", msg );
  prevtoken = YES;
}

static void paramdcl( void ) {
  do {
    dcl();
  } while ( tokentype == ',' );
  if ( tokentype != ')' ) {
    errmsg( "missing ) in parameter declaration\n" );
  }
}

static int typequal( void ) {
  static char *typeq[] = { "const", "volatile", "auto", "static", "register" };
  char *p = token;
  int num = sizeof( typeq ) / sizeof( typeq[ 0 ] );
  int i;
  for ( i = 0; i < num && strcmp( typeq[ i ], p ) != 0; i++ )
    ;
  if ( i == num ) {
    return NO;
  }
  return YES;
}
