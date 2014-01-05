/*
 * Project: bookmark
 * Interface: book.h
 *
 * underlying interface for bookmark
 */
#ifndef _book_h
#define _book_h "book.h"

#include <stdio.h>
#include <time.h>

#define STRING_SIZE 128

typedef struct BookCDT {
  char name[ STRING_SIZE ];
  char topic[ STRING_SIZE ];
  int page;
  int chap;
  time_t date;
} *Book;


Book newBook();

int compare( const void *a, const void *b );

void inputBook( FILE *in, Book b );

void outputBook( FILE *out, Book b );

int getline( FILE *in, char str[ ], int lim ); 

void print( Book b );

#endif
