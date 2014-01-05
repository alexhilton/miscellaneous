/*
 * Project: Bookmark
 * 
 * Implementation of interface book.h
 * the underlying implementation of class Bookmark
 */
#include "book.hh"
#include <string>
#include <ctime>

Book::Book() {
	name = "unkown";
	topic = "unkown";
	page = 0;
	date = time( 0 );
	chap = 0;
}

Book::Book( const string &n, unsigned long d, const string &t,
		   unsigned int p, unsigned int c ) {
	name = n;
	date = d;
	topic = t;
	page = p;
	chap = c;
}

Book::Book( const string &n, unsigned int c, const string &t ) {
	name = n;
	chap = c;
	topic = t;
	date = time( 0 );
	page = 0;
}

Book::Book( const string &n ) {
	name = n;
	chap = 0;
	topic = "unkown";
	page = 0;
	date = time( 0 );
}

string Book::getTopic() const {
	return topic;
}

unsigned int Book::getChap() const {
	return chap;
}
string Book::getName() const {
	return name;
}

unsigned long Book::getDate() const {
	return date;
}

unsigned int Book::getPage() const {
	return page;
}

void Book::setChap( unsigned int ch ) {
	chap = ch;
}

void Book::setName( const string &n ) {
	name = n;
}

void Book::setTopic( const string &t ) {
	topic = t;
}

void Book::setDate( unsigned long &d ) {
	date = d;
}

void Book::setPage( unsigned int &p ) {
	page = p;
}

int Book::compare( const Book &b1, const Book &b2 ) {
	return b1.date - b2.date;
}

bool Book::operator<( const Book &b1 ) const {
	return date < b1.date;
}

bool Book::operator>( const Book &b1 ) const {
	return date > b1.date;
}

bool Book::operator==( const Book &b ) const {
	return name == b.name;
}

Book Book::operator=( const Book &b ) {
	Book one;
	one.name = b.name;
	one.topic = b.topic;
	one.page = b.page;
	one.date = b.date;
	return one;
}

void Book::printLine( char ch, int size ) {
	int i;
	for ( i = 0; i < size; i++ ) {
		cout << ch;
	}
	cout << endl;
}

void Book::output() {
	int size = 50;
	printLine( '=', size );
	cout << "Name:\t " << name << endl;
	cout << "Chap:\t " << chap << endl;
	cout << "Topic:\t " << topic << endl;
	cout << "Page:\t " << page << endl;
	cout << "Date:\t " << ctime( (long *) &date );
	printLine( '=', size );
	cout << endl << endl;
}

void Book::input() {
	string str;
	cout << "Name: ";
	getline( cin, str );
	name = str;
	cout << "Chap: ";
	getline( cin, str );
	chap = atoi( str.c_str() );
	cout << "Topic: ";
	getline( cin, str );
	topic = str;
	cout << "Page: ";
	getline( cin, str );
	page = atoi( str.c_str() );
	date = time( 0 );
}

void Book::output( ofstream &out ) {
	out << name << endl;
	out << chap << endl;
	out << topic << endl;
	out << page << endl;
	out << date << endl;
}

void Book::input( ifstream &in ) {
	string str;
	getline( in, str );
	name = str;
	getline( in, str );
	chap = atoi( str.c_str() );
	getline( in, str );
	topic = str;
	getline( in, str );
	page = atoi( str.c_str() );
	date = time( 0 );
}

/*
ostream &Book::operator<<( ostream &out, const Book &b ) {
	printLine( out, '=', 50 );
	out << "Name:\t " << b.getName() << endl;
	out << "Chap:\t " << b.getChap() << endl;
	out << "Topic:\t " << b.getTopic() << endl;
	out << "Page:\t " << b.getPage() << endl;
	unsigned long d = b.getDate();
	out << "Date:\t " << ctime( (long *) &d );
	printLine( out, '=', 50 );
	out << endl << endl;
	return out;
}

istream &Book::operator>>( istream &in, const Book &b ) {
	string str;
	cout << "Name: ";
	getline( in, str );
	b.setName( str );
	cout << "Chap: ";
	getline( in, str );
	unsigned int a = atoi( str.c_str() );
	b.setChap( a );
	cout << "Topic: ";
	getline( in, str );
	b.setTopic( str );
	cout << "Page: ";
	getline( in, str );
	a = atoi( str.c_str() );
	b.setPage( a );
	unsigned long d = time( 0 );
	b.setDate( d );
	return in;
}


ofstream &Book::operator<<( ofstream &out, const Book &b ) {
	out << b.getName() << endl;
	out << b.getChap() << endl;
	out << b.getTopic() << endl;
	out << b.getPage() << endl;
	unsigned long d = b.getDate();
	out << ctime( (long *) &d );
	return out;
}

ifstream &Book::operator>>( ifstream &in, Book &b ) {
	string str;
	getline( in, str );
	b.setName( str );
	getline( in, str );
	unsigned int a = atoi( str.c_str() );
	b.setChap( a );
	getline( in, str );
	b.setTopic( str );
	getline( in, str );
	a = atoi( str.c_str() );
	b.setPage( a );
	getline( in, str );
	unsigned long d = atol( str.c_str() );
	b.setDate( d );
	return in;
}
*/
