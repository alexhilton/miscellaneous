/*
 * Project: Bookmark
 * Main program
 *
 * main program of project bookmark
 */
#include "book.h"
#include "bookmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main( int argc, char *argv[ ] ) {
  char ch;
  char optstring[ ] = "abcd";
  char str[ STRING_SIZE ];
  int flag = 1;

  /* options processing */
  while ( (ch = getopt( argc, argv, optstring )) != EOF ) {
    switch ( ch ) {
    case 'a':
      printf( "option -a caught\n" );
      break;
    case 'b':
      printf( "optiona -b caught\n" );
      break;
    case 'c':
      printf( "option -c caugth\n" );
      break;
    case 'd':
      printf( "option -d caugth\n" );
      break;
    default:
      printf( "Unkown option\n" );
      break;
    }
  }
  char filename[ ] = "bookmark.dat";
  Bookmark bm = newBookmark();
  FILE *fptr = fopen( filename, "r+" );
  if ( fptr == NULL ) {
    perror( filename );
    exit( EXIT_FAILURE );
  }
  inputBookmark( fptr, bm );
  fclose( fptr );

  Book b;
  printf( "Welcome to bookmark program\n" );
  while ( flag ) {
    printf( "[l]ist\t[a]dd\t[d]elete\t[o]pen\t[c]lose\t[q]uit\n" );
    printf( ">" );
    getline( stdin, str, STRING_SIZE );
    ch = str[ 0 ];
    switch ( ch ) {
    case 'l':
      listBookmark( bm, str[ 2 ] );
      break;
    case 'a':
      b = newBook();
      printf( "Name: " );
      getline( stdin, b->name, STRING_SIZE );
      printf( "Chap: " );
      getline( stdin, str, STRING_SIZE );
      b->chap = atoi( str );
      printf( "Topic: " );
      getline( stdin, b->topic, STRING_SIZE );
      printf( "Page: " );
      getline( stdin, str, STRING_SIZE );
      b->page = atoi( str );
      b->date = time( 0 );
      addBook( bm, b );
      break;
    case 'd':
      printf( "Book to delete: " );
      getline( stdin, str, STRING_SIZE );
      deleteBook( bm, str );
      break;
    case 'o':
      printf( "Book to open: " );
      getline( stdin, str, STRING_SIZE );
      openBook( bm, str );
      break;
    case 'c':
      b = newBook();
      printf( "Name: " );
      getline( stdin, b->name, STRING_SIZE );
      printf( "Chap: " );
      getline( stdin, str, STRING_SIZE );
      b->chap = atoi( str ); 
      printf( "Topic: " );
      getline( stdin, b->topic, STRING_SIZE );
      printf( "Page: " );
      getline( stdin, str, STRING_SIZE );
      b->page = atoi( str );
      b->date = time( 0 );
      closeBook( bm, b );
      break;
    case 'q':
      flag = 0;
      break;
    default:
      printf( "Unkown command\n" );
      break;
    }
  }
  outputBookmark( fptr, bm );
  deleteBookmark( bm );
  return 0;
}
