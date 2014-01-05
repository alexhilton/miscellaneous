/**
 * countkey.c
 * counting the number of keywords in a C source file.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LEN 100 /* max length of a word */

typedef struct Key Key;

struct Key {
  char *word;
  int count;
};

Key keytab[] = {
  "auto", 0, "break", 0, "case", 0, "char", 0, "const", 0, "continue", 0,
  "default", 0, "do", 0, "double", 0, "else", 0, "enum", 0, "extern", 0,
  "float", 0, "for", 0, "goto", 0, "if", 0, "inline", 0, "int", 0, 
  "long", 0, "register", 0, "restrict", 0, "return", 0, "short", 0,
  "signed", 0, "sizeof", 0, "static", 0, "struct", 0, "switch", 0,
  "typedef", 0, "union", 0, "unsigned", 0, "void", 0, "volatile", 0, "while", 0,
};

char getword( char *word, int limit );
int binsearch( char *workd, Key *key, int size );
char getch();
void ungetch( char ch );
char buffer[ MAX_WORD_LEN ];
int bufp = 0;
int shield = 0; /* whether it is strings, comments, preprocessors */

/* main program, counting C keywords */
int main( int argc, char **argv ) {
  int n;
  char word[ MAX_WORD_LEN ];
  int keynum = sizeof( keytab ) / sizeof( keytab[ 0 ] );
  while ( getword( word, MAX_WORD_LEN ) != EOF ) {
    if ( isalpha( *word ) && !shield ) {
      if( (n = binsearch( word, keytab, keynum )) >= 0 ) {
	keytab[ n ].count++;
      }
    }
  }
  for ( n = 0;  n < keynum; n++ ) {
    printf( "%4d %s\n", keytab[ n ].count, keytab[ n ].word );
  }
  return 0;
}

/* binsearch */
int binsearch( char *word, Key *key, int keynum ) {
  int cond;
  int low, high, mid;

  low = 0;
  high = keynum - 1;
  while ( low <= high ) {
    mid = ( low + high ) / 2;
    if ( (cond = strcmp( word, key[ mid ].word )) < 0 ) {
      high = mid - 1;
    } else if ( cond > 0 ) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1; /* no match found */
}

/* get next word from input stream. */
char getword( char *word, int limit ) {
  char ch;
  char *w = word;

  while ( isspace( ch = getch() ) )
    ;
  if ( ch != EOF ) {
    *w++ = ch;
  }

  if ( ch == '"' ) {
    if ( !shield ) {
      shield = 1;
    } else {
      shield = 0;
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

char getch() {
  return bufp > 0 ? buffer[ --bufp ] : getchar();
}

void ungetch( char ch ) {
  if ( bufp >= MAX_WORD_LEN ) {
    printf( "error: pushing too many chars back\n" );
  } else {
    buffer[ bufp++ ] = ch;
  }
}
