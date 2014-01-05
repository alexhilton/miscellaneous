/*
 * Project: Bookmark
 * interface: bookmark.h
 *
 * defines class Bookmark
 */
#ifndef _bookmark_h
#define _bookmark_h "bookmark.h"

#include "book.h"
#include <fstream>
#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <ctime>
using namespace std;

class Bookmark {
public:
	Bookmark();
	Bookmark( const string &fn );
	~Bookmark();
	void listBook( char flag );
	void addBook( const Book &b );
	void deleteBook( const Book &b );
	deque< Book >::iterator searchBook( const Book &b );
	void openBook( const Book &b );
	void closeBook( const Book &b );
	void sortBook();
	
private:
	deque< Book > book; // list of books
	string filename; // file of storage of bookmark
	unsigned int number; // total number of books on shelf
	//void output( ofstream &out, Book &b );
	//void (*listFunc)();
	//void listAll();
	//void listGen();
	//bool compare( const Book &b1, const Book &b2 );
};

#endif
