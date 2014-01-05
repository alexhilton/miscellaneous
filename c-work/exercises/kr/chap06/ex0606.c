/**
 * ex0606.c
 * solution to ex0606
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 1337
#define MAX_WORD_LEN 50

typedef struct Node *Node;

struct Node {
  char name[ MAX_WORD_LEN ];
  char def[ MAX_WORD_LEN ];
  struct Node *next;
};

static Node hashtable[ HASH_SIZE ];

/* hashcode: to compute the hash code */
static unsigned hashcode( char *word );
/* put name and its macro defination into hashtable */
static Node install( char *name, char *def );
/* look for a macro in hash table */
static Node lookup( char *name );
/* 
 * remove a macro difination 
 * arg node is the one which is removed, or NULL, if no match found
 */
static void undef( char *name, Node node );
/* free the storage of hashtable */
static void hashfree();
/* traverse the hashtable */
static void hashwalk();
/* get next word from input */
static char getword( char *word, int limit );
/* get next char from input */
static char getch();
/* push back a char onto input stream */
static void ungetch( char ch );
/* input buffer */
static char buffer[ MAX_WORD_LEN ];
/* input buffer pointer */
static int bufp = 0;

/* main program */
int main( int argc, char **argv ) { 
  char word[ MAX_WORD_LEN ];
  Node node;
  char def[ MAX_WORD_LEN ];
  while ( getword(word, MAX_WORD_LEN) != EOF ) {
    if ( *word == '#' ) {
      printf( "%s", word );
      getword( word, MAX_WORD_LEN );
      if ( isspace( *word ) ) {
	printf( "%s", word );
	getword( word, MAX_WORD_LEN );
      }
      if ( strcmp( word, "define" ) == 0 ) {
	printf( "%s", word );
	/* we got one macro definition */
	getword( word, MAX_WORD_LEN );
	printf( "%s", word );
	if ( isspace( *word ) ) {
	  getword( word, MAX_WORD_LEN );
	  printf( "%s", word );
	}
	getword( def, MAX_WORD_LEN );
	printf( "%s", def );
	if ( isspace( *def ) ) {
	  getword( def, MAX_WORD_LEN );
	  printf( "%s", def );
	}
	if ( (node = install( word, def )) == NULL ) {
	  //printf( "error: low memory\n" );
	  break;
	} else {
	 // printf( "installed '%s -- %s'\n", node->name, node->def );
	}
      } else {
	if ( (node = lookup( word )) != NULL ) {
	  printf( "%s", node->def );
	} else {
	  printf( "%s", word );
	}
      }
    } else if ( isalpha( *word ) ) {
      if ( (node = lookup( word )) != NULL ) {
	//printf( "subsitute '%s' with '%s'\n", node->name, node->def );
	printf( "%s", node->def );
      } else {
	printf( "%s", word );
      }
    } else {
      printf( "%s", word );
    }
  }
  //printf( "after install, the hashtable looks like:\n" );
  //hashwalk();
  hashfree();
  return 0;
}

static unsigned hashcode( char *word ) {
  unsigned code;
  for ( code = 0; *word != '\0'; word++ ) {
    code = *word + 31 * code;
  }
  return code % HASH_SIZE;
}

static Node lookup( char *word ) {
  Node ret;
  for ( ret = hashtable[ hashcode( word ) ]; ret != NULL; ret = ret->next ) {
    if ( strcmp( ret->name, word ) == 0 ) {
      return ret;
    }
  }
  return NULL; /* no match found */
}

static Node install( char *word, char *def ) {
  Node node;
  unsigned code = hashcode( word );
  for ( node = hashtable[ code ]; node != NULL; node = node->next ) {
    if ( strcmp( node->name, word ) == 0 ) {
      /* already defined, we supersede it */
      strcpy( node->def, def );
      return node;
    }
  }
  if ( (node = (Node) malloc( sizeof( *node ) )) == NULL ) {
    return NULL;
  }
  strcpy( node->name, word );
  strcpy( node->def, def );
  /* 
   * you cannot just write node->next = NULL;
   * because there is no pointer pointing to node
   * after looking up, some pointer and node point to the same thing NULL
   * but if you got something like node->next = null;
   * then you can alloc space for node->next, and fill the structure.
   */
  node->next = hashtable[ code ];
  hashtable[ code ] = node;
  return node;
}

static void undef( char *word, Node macro ) {
  Node node, prev;
  unsigned code = hashcode( word );
  prev = node = hashtable[ code ];
  if ( node == NULL ) {
    strcpy( macro->name, "####" );
    return;
  }
  if ( strcmp( node->name, word ) == 0 ) {
    strcpy( macro->name, node->name );
    strcpy( macro->def, node->def );
    macro->next = NULL;
    if ( node->next == NULL ) {
      free( node );
      hashtable[ code ] = NULL;
    }
    return;
  }

  /* attention here: you have to assign node to prev, before iterate */
  for ( node = node->next; node != NULL; prev = node, node = node->next ) {
    if ( strcmp( node->name, word ) == 0 ) {
      strcpy( macro->name, node->name );
      strcpy( macro->def, node->def );
      macro->next = NULL;
      /* you cannot write like this:
      next = node;
      next = next->next;
      free( node );
      * it does not work we have to make something like prev->next = node->next */
      /* attention: prev = node->next, does not work */
      prev->next = node->next;
      free( node );
      return;
    }
  }
  /* no match found */
  strcpy( macro->name, "####" );
}

static void hashfree() {
  Node node, next;
  int i;
  for ( i = 0; i < HASH_SIZE; i++ ) {
    for ( node = hashtable[i]; node != NULL; ) {
      next = node->next;
      free( node );
      node = next;
    }
  }
}

static void hashwalk() {
  Node node;
  int i, hasNode;
  printf( "====================================\n" );
  for ( i = 0; i < HASH_SIZE; i++ ) {
    hasNode = 0;
    for ( node = hashtable[i]; node != NULL; node = node->next ) {
      if ( node == hashtable[ i ] ) {
	printf( "hashtable[%d]: ", i );
      }
      printf( "'%s - %s'; ", node->name, node->def );
      hasNode = 1;
    }
    if ( hasNode ) {
      printf( "\n" );
    }
  }
  printf( "====================================\n" );
}

static char getword( char *word, int limit ) {
  char ch;
  char *w = word;

  ch = getch();
  if ( isspace( ch ) ) {
    for ( *w++ = ch; --limit > 0; w++ ) {
      if ( !isspace( *w = getch() ) ) {
	ungetch( *w );
	break;
      }
    }
    *w = '\0';
    return ch;
  }

  if ( ch != EOF ) {
    *w++ = ch;
  }

  if ( !isalnum( ch ) && ch != '_' ) {
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
