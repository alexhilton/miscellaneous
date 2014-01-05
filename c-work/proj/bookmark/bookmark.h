/*
 * Project: Bookmark
 * Interface
 *
 * Interface for high-level interface
 */
#ifndef _bookmark_h
#define _bookmark_h "bookmark.h"

#include "book.h"
#include <stdio.h>

#define MAX_SIZE 100

typedef struct BookmarkCDT *Bookmark;

Bookmark newBookmark();

void deleteBookmark( Bookmark bm );

void addBook( Bookmark bm, Book b );

void deleteBook( Bookmark bm, char n[ ] );

void listBookmark( Bookmark bm, char flag );

Book searchBook( Bookmark bm, char n[ ] );

void openBook( Bookmark bm, char n[ ] );

void closeBook( Bookmark bm, Book b );

void inputBookmark( FILE *in, Bookmark bm );

void outputBookmark( FILE *out, Bookmark bm );

#endif
