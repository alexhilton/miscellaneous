/*
 * Project: Bookmark
 * Implementation
 *
 * Implementation of interface book.h
 */
#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* static void error( char str[ ] ) {
  printf( "%s\n", str );
  exit( EXIT_FAILURE );
} */

static void printLine( char ch, int size ) {
  int i;
  for ( i = 0; i < size; i++ ) {
    putchar( ch );
  }
  putchar( '\n' );
}

Book newBook() {
  Book book = malloc( sizeof( *book ) );
  strcpy( book->name, "unkown" );
  strcpy( book->topic, "unkown" );
  book->page = 0;
  book->chap = 0;
  book->date = time( 0 );
  return book;
}

void print( Book b ) {
  int size = 80;
  printLine( '=', size );
  printf( "Name:\t %s\n", b->name );
  printf( "Chap:\t %d\n", b->chap );
  printf( "Topic:\t %s\n", b->topic );
  printf( "Page:\t %d\n", b->page );
  printf( "Date:\t %s", ctime( &b->date ) );
  printLine( '=', size );
}

int compare( const void *a, const void *b ) {
  Book b1 = ( Book ) a;
  Book b2 = ( Book ) b;
  int cmp = b1->date - b2->date;
  if ( cmp > 0 ) {
    return -1;
  } else if ( cmp < 0 ) {
    return 1;
  } else {
    return 0;
  }
}

int getline( FILE *in, char str[ ], int lim ) {
  int i;
  char ch;
  for ( i = 0; i < lim && (ch = fgetc(in)) != EOF; i++ ) {
    if ( ch == '\n' ) {
      str[ i ] = '\0';
      return i;
    } else {
      str[ i ] = ch;
    }
  }
  str[ i ] = '\0';
  return i;
}

void inputBook( FILE *in, Book b ) {
  char str[ STRING_SIZE ];
  getline( in, b->name, STRING_SIZE ); 
  getline( in, str, STRING_SIZE );
  b->chap = atoi( str );
  getline( in, b->topic, STRING_SIZE );
  getline( in, str, STRING_SIZE );
  b->page = atoi( str );
  getline( in, str, STRING_SIZE );
  b->date = atol( str );
}

void outputBook( FILE *out, Book b ) {
  fprintf( out, "%s\n", b->name );
  fprintf( out, "%d\n", b->chap );
  fprintf( out, "%s\n", b->topic );
  fprintf( out, "%d\n", b->page );
  fprintf( out, "%ld\n", b->date );
}
