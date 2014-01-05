/**
 * ex0603.c
 * solution to ex0603
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LEN 50 /* max length of a word */
#define MAX_LINE 500 /* max number of lines in a file */

typedef struct Node Node;

struct Node {
  char word[ MAX_WORD_LEN ];
  int lines[ MAX_LINE ]; /* lines on which word appears */
  int size; /* size of lines */
  struct Node *left; /* left child */
  struct Node *right; /* right child */
};

static const char *noiseword[] = {
  "a", "an", "and", "am", "are", "for", "is", "of", "so", "the", "to", "was"
};

/* 
 * add a new word into the tree
 * we might add it into a group resided in a node of the tree.
 * or we make a new home(node) for it, if it is a new guy.
 */
static Node *addtree( Node *tree, char word[] );
/* in-order traversing the tree */
static void treewalk( Node *tree );
/* free storage of tree */
static void treefree( Node *tree );
/* get next word from input without taking comments and strings in account */
static char getword( char *word, int limit );
/* get next char */
static char getch();
/* push back a char onto input stream */
static void ungetch( char ch );
/* whether the word is a noise word, e.g. and, so, on etc */
static int isnoise( char *word );
/* input buffer */
static char buffer[ MAX_WORD_LEN ];
/* input buffer pointer */
static int bufp = 0;
/* line number */
static int line = 1;

/* main prog */
int main( int argc, char **argv ) {
  char word[ MAX_WORD_LEN ];
  Node *tree = NULL;
  while ( getword( word, MAX_WORD_LEN ) != EOF ) {
    if ( isalpha( *word ) && !isnoise( word ) ) {
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
    strcpy( tree->word, word );
    tree->lines[ tree->size++ ] = line;
    tree->left = NULL;
    tree->right = NULL;
  } else {
    if ( (cmp = strcmp( tree->word, word )) == 0 ) {
      if ( tree->lines[ tree->size-1 ] != line ) {
	tree->lines[ tree->size++ ] = line;
      }
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
    printf( "'%s' is on lines of {", tree->word );
    for ( i = 0; i < tree->size; i++ ) {
      printf( "%d, ", tree->lines[ i ] );
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

static char getword( char *word, int limit ) {
  char ch;
  char *w = word;

  while ( (ch = getch()) == ' ' || ch == '\t' )
    ;
  if ( ch != EOF ) {
    *w++ = ch;
  }

  if ( ch == '\n' ) {
    line++;
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

static int isnoise( char *word ) {
  int high = sizeof( noiseword ) / sizeof( noiseword[ 0 ] ) - 1;
  int low = 0;
  int mid;
  int cmp;
  while ( low <= high ) {
    mid = ( high + low ) / 2;
    if ( (cmp = strcmp( noiseword[ mid ], word )) == 0 ) {
      return 1;
    } else if ( cmp > 0 ) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return 0;
}
