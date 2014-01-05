/**
 * ex0602.c
 * solution to ex0602
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 1000 /* max size of words in a file */
#define MAX_WORD_LEN 50 /* max length of a word in a file */

typedef struct Node Node;

struct Node {
  char words[ MAX_SIZE ][ MAX_WORD_LEN ];
  int size; /* current number of words */
  struct Node *left; /* left child */
  struct Node *right; /* right child */
};

static int number = 6; /* the comparision of first # of chars */

/* 
 * add a new word into the tree
 * we might add it into a group resided in a node of the tree.
 * or we make a new home(node) for it, if it is a new guy.
 */
static Node *addtree( Node *tree, char word[] );
/* in-order traversing the tree */
static void treewalk( Node *tree );
static void treefree( Node *tree );
/*
 * our string comparision function.
 * it acts much like standard strcmp, except:
 * first, it ignore case.
 * second it compares first number of chars only.
 * finally it thinks in alphabetical order.
 */
static int strncasecmp( char *str1, char *str2 );
/* get next word from input without taking comments and strings in account */
static char getword( char *word, int limit );
/* get next char */
static char getch();
/* push back a char onto input stream */
static void ungetch( char ch );
/* input buffer */
static char buffer[ MAX_WORD_LEN ];
/* input buffer pointer */
static int bufp = 0;
/* in comments or not */
static int comment = 0;
/* in strings or not */
static int quote = 0;

/* main prog */
int main( int argc, char **argv ) {
  if ( argc == 2 ) {
    number = atoi( ++(*++argv) );
  } else if ( argc != 1 ) {
    printf( "usage: prog -n\n" );
    return 0;
  }

  char word[ MAX_WORD_LEN ];
  Node *tree = NULL;
  while ( getword( word, MAX_WORD_LEN ) != EOF ) {
    if ( isalpha( *word ) && !comment && !quote ) {
      tree = addtree( tree, word );
    }
  }
  treewalk( tree );
  treefree( tree );
  return 0;
}

static Node *addtree( Node *tree, char *word ) {
  int cmp;
  if ( tree == NULL ) {
    tree = (Node *) malloc( sizeof( *tree ) );
    tree->size = 0;
    strcpy( tree->words[ tree->size++ ], word );
    tree->left = NULL;
    tree->right = NULL;
  } else {
    if ( (cmp = strncasecmp( tree->words[ 0 ], word )) == 0 ) {
      strcpy( tree->words[ tree->size++ ], word );
    } else if ( cmp > 0 ) {
      tree->left = addtree( tree->left, word );
    } else {
      tree->right = addtree( tree->right, word );
    }
  }
  return tree;
}

static void treewalk( Node *tree ) {
  if ( tree != NULL ) {
    treewalk( tree->left );
    int i;    
    printf( "{" );
    for ( i = 0; i < tree->size; i++ ) {
      printf( "%s, ", tree->words[ i ] );
    }
    printf( "}\n" );
    treewalk( tree->right );
  }
}

static void treefree( Node *tree ) {
  if ( tree != NULL ) {
    treefree( tree->left );
    treefree( tree->right );
    free( tree );
  }
}

static int strncasecmp( char *str1, char *str2 ) {
  char p, q;
  p = q = 'a';
  int i = 0;
  while ( p == q && i < number ) {
    if ( p == '\0' ) {
      return 0;
    }
    p = tolower( *str1++ );
    q = tolower( *str2++ );
    i++;
  }
  return p - q;
}

static char getword( char *word, int limit ) {
  char ch;
  char *w = word;

  while ( isspace( ch = getch() ) )
    ;
  if ( ch != EOF ) {
    *w++ = ch;
  }

  if ( ch == '"' ) {
    if ( !quote ) {
      quote = 1;
    } else {
      quote = 0;
    }
  }

  if ( ch == '/' ) {
    if ( (ch = getch()) == '*' ) {
      comment = 1;
    } else {
      ungetch( ch );
    }
  }

  if ( ch == '*' ) {
    if ( (ch = getch()) == '/' ) {
      comment = 0;
    } else {
      ungetch( ch );
    }
  }

  if ( !isalpha( ch ) && ch != '_' ) {
    *w = '\0';
    return ch;
  }

  for ( ; --limit > 0; w++ ) {
    if ( !isalnum( *w = getch() ) && *w != '_' ) {
      ungetch( *w );
      break;
    }
  }
  *w = '\0';
  return *word;
}

static char getch() {
  return bufp > 0 ? buffer[ --bufp ] : getchar();
}

static void ungetch( char ch ) {
  if ( bufp >= MAX_WORD_LEN ) {
    printf( "error: pushing too many chars back\n" );
  } else {
    buffer[ bufp++ ] = ch;
  }
}
