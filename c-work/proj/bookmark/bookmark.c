/*
 * Project: bookmark
 * Implementation
 *
 * implementation of interface bookmark.h
 */
#include "bookmark.h"
#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct BookmarkCDT {
  Book book[ MAX_SIZE ];
  int size;
};

Bookmark newBookmark() {
  Bookmark bm = malloc( sizeof( *bm ) );
  bm->size = 0;
  return bm;
}

void deleteBookmark( Bookmark bm ) {
  int i;
  for ( i = 0; i < bm->size; i++ ) {
    free( bm->book[ i ] );
  }
  free( bm );
}

Book searchBook( Bookmark bm, char n[ ] ) {
  int i;
  for ( i = 0; i < bm->size; i++ ) {
    if ( strcasecmp( n, bm->book[ i ]->name ) == 0 ) {
      return bm->book[ i ];
    }
  }
  return NULL;
}

void addBook( Bookmark bm, Book b ) {
  bm->book[ bm->size++ ] = b;
}

void deleteBook( Bookmark bm, char n[ ] ) {
  int i;
  for ( i = 0; i < bm->size; i++ ) {
    if ( strcasecmp( n, bm->book[i]->name ) == 0 ) {
      break;
    }
  }
  if ( i >= bm->size ) {
    return; /* Not found */
  }
  Book tmp = bm->book[ i ];
  for ( ; i < bm->size-1; i++ ) {
    bm->book[ i ] = bm->book[ i+1 ];
  }
  free( tmp );
}

void openBook( Bookmark bm, char n[ ] ) {
  Book index = searchBook( bm, n );
  if ( index == NULL ) {
    printf( "Book: '%s' is not in the bookmark\n", n );
    return;
  }
  print( index );
}

void closeBook( Bookmark bm, Book b ) {
  Book index = searchBook( bm, b->name );
  if ( index == NULL ) {
    printf( "Book: '%s' is not in the bookmark\n", b->name );
    return;
  }
  index->page = b->page;
  strcpy( index->topic, b->topic );
  index->date = b->date;
}

void inputBookmark( FILE *in, Bookmark bm ) {
  char str[ STRING_SIZE ];
  /* fscanf( in, "%d", &bm->size );
  fgetc( in ); */
  getline( in, str, STRING_SIZE );
  bm->size = atoi( str );
  int i;
  for ( i = 0; i < bm->size; i++ ) {
    bm->book[ i ] = newBook();
    inputBook( in, bm->book[ i ] );
  }
}

void outputBookmark( FILE *out, Bookmark bm ) {
  fprintf( out, "%d\n", bm->size );
  int i;
  for ( i = 0; i < bm->size; i++ ) {
    outputBook( out, bm->book[ i ] );
  }
}

void listBookmark( Bookmark bm, char flag ) {
  int size;
  if ( flag == 'a' ) {
    size = bm->size;
  } else if ( flag == 'g' ) {
    size = 5;
  }
  int i;
  for ( i = 0; i < size; i++ ) {
    print( bm->book[ i ] );
    putchar( '\n' );
  }
}
