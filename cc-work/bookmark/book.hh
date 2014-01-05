/*
 * Project: Bookmark
 * Interface: book.h
 *
 * define underlying interface for class Bookmark
 */
#ifndef _book_h
#define _book_h	"book.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
	Book();
	Book( const string &n, unsigned long date, const string &topic, 
		unsigned int page, unsigned int chap );
	Book( const string &n, unsigned int c, const string &t );
	Book( const string &n );
	string getName() const;
	unsigned long getDate() const;
	unsigned int getPage() const;
	string getTopic() const;
	unsigned int getChap() const;
	void setChap( unsigned int ch );
	void setName( const string &n );
	void setDate( unsigned long &d );
	void setTopic( const string &t );
	void setPage( unsigned int &p );
	int compare( const Book &b1, const Book &b2 );
	bool operator<( const Book &b ) const;
	bool operator>( const Book &b ) const;
	bool operator==( const Book &b ) const;
	Book operator=( const Book &b );
	// IO among classes are the most frustrating things
	void output(); // for standard output
	void input(); // for standard input
	void output( ofstream &out );
	void input( ifstream &in );
	/*friend ostream &operator<<( ostream &out, const Book &b );
	friend istream &operator>>( istream &in, Book &b );
	friend ifstream &operator>>( ifstream &in, Book &b );
	friend ofstream &operator<<( ofstream &out, const Book &b );*/
private:
	string name;
	string topic;
	unsigned long date;
	unsigned int page;
	unsigned int chap;
	void printLine( char ch, int size );
};

#endif
