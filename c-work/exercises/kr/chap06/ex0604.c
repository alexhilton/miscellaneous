/**
 * ex0604.c
 * solution to ex0604
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LEN 50 /* max length of a word */
#define MAX_SIZE 5000 /* max number of distinct words in a file */

typedef struct Node Node;

struct Node {
  char word[ MAX_WORD_LEN ];
  int count; /* count of word */
  struct Node *left; /* left child */
  struct Node *right; /* right child */
};

static Node *wordtab[ MAX_SIZE ];
static int wordsize = 0;
/* 
 * add a new word into the tree
 * we might add it into a group resided in a node of the tree.
 * or we make a new home(node) for it, if it is a new guy.
 */
static Node *addtree( Node *tree, char word[] );
/* in-order traversing the tree */
static void treewalk( Node *tree );
/* release the storage occupied by tree */
static void treefree( Node *tree );
/* get next word from input without taking comments and strings in account */
static char getword( char *word, int limit );
/* get next char */
static char getch();
/* push back a char onto input stream */
static void ungetch( char ch );
/* quick sort */
static void quicksort( Node **a, int left, int right );
static void swap( Node **a, int left, int right );
/* compare func for qsort */
static int compare( const void *a, const void *b );
/* input buffer */
static char buffer[ MAX_WORD_LEN ];
/* input buffer pointer */
static int bufp = 0;

/* main prog */
int main( int argc, char **argv ) {
  char word[ MAX_WORD_LEN ];
  Node *tree = NULL;
  while ( getword( word, MAX_WORD_LEN ) != EOF ) {
    if ( isalpha( *word ) ) {
      tree = addtree( tree, word );
    }
  }
  treewalk( tree );
  /*
   * question:
   * why standard qsort does not work
   */
  quicksort( wordtab, 0, wordsize-1 );
  //qsort( (void **) wordtab, wordsize, sizeof( wordtab[ 0 ] ), compare );
  int i;
  for ( i = 0; i < wordsize; i++ ) {
    printf( "\t%-20s\t%d\n", wordtab[ i ]->word, wordtab[ i ]->count );
  }
  treefree( tree );
  return 0;
}

static Node *addtree( Node *tree, char *word ) {
  int cmp;
  if ( tree == NULL ) {
    tree = (Node *) malloc( sizeof( *tree ) );
    tree->count = 1;
    strcpy( tree->word, word );
    tree->left = NULL;
    tree->right = NULL;
  } else {
    if ( (cmp = strcmp( tree->word, word )) == 0 ) {
      tree->count++;
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
    wordtab[ wordsize++ ] = tree;
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

static void quicksort( Node *key[], int left, int right ) {
  int i, last;
  if ( left >= right ) {
    return;
  }
  swap( key, left, (left + right) / 2 );
  last = left;
  for ( i = left+1; i <= right; i++ ) {
    //if ( key[ i ]->count < key[ left ]->count ) {
    if ( compare( key[i], key[left] ) < 0 ) {
      swap( key, ++last, i );
    }
  }
  swap( key, left, last );
  quicksort( key, left, last-1 );
  quicksort( key, last+1, right );
}

static void swap( Node *key[], int i, int j ) {
  Node *tmp = key[ i ];
  key[ i ] = key[ j ];
  key[ j ] = tmp;
}

static char getword( char *word, int limit ) {
  char ch;
  char *w = word;

  while ( isspace( ch = getch() ) )
    ;
  if ( ch != EOF ) {
    *w++ = ch;
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

static int compare( const void *a, const void *b ) {
  Node *t1 = (Node *) a;
  Node *t2 = (Node *) b;
  int cmp = t1->count - t2->count;
  if ( cmp == 0 ) {
    return 0;
  } else if ( cmp > 0 ) {
    return 1;
  } else {
    return -1;
  }
}
