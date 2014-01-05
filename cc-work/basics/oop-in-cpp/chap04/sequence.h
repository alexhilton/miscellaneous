/*
 * class sequence defined here.
 */
#ifndef _sequence_h
#define _sequence_h

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Sequence {
private:
  string filename;
  ifstream in;
  ofstream out;
protected:
  enum { MAX_SIZE = 50 };
  string s[ MAX_SIZE ];
  int last;
public:
  bool addItem( int index, const string &item );
  bool deleteItem( int index );
  void output() const;
  Sequence() : last( -1 ) {}
  Sequence( const char *fname );
  ~Sequence();
};

bool Sequence::addItem( int index, const string &item ) {
  if ( last == MAX_SIZE-1 || index < 0 || index > last+1 ) {
    return false;
  }
  int i;
  for ( i = last; i >= index; i-- ) {
    s[ i+1 ] = s[ i ];
  }
  s[ index ] = item;
  last++;
  return true;
}

bool Sequence::deleteItem( int index ) {
  if ( index < 0 || index > last ) {
    return false;
  }
  int i;
  for ( i = index; i < last; i++ ) {
    s[ i ] = s[ i+1 ];
  }
  last--;
  return true;
}

void Sequence::output() const {
  int i;
  for ( i = 0; i <= last; i++ ) {
    cout << i << "  " << s[ i ] << endl;
  }
}

Sequence::Sequence( const char *fname ) {
  last = -1;
  filename = fname;
  in.open( fname );
  if ( !in ) {
    return;
  }
  while ( last < MAX_SIZE-1 && getline( in, s[ last+1 ] ) ) {
    last++;
  }
  in.close();
}

Sequence::~Sequence() {
  if ( filename == "" ) {
    return;
  }
  out.open( filename.c_str() );
  int i;
  for ( i = 0; i <= last; i++ ) {
    out << s[ i ] << endl;
  }
  out.close();
}

// derive a class SortedSeq from Sequence
class SortedSeq : public Sequence {
private:
  using Sequence::addItem;
protected:
  void sort();
public:
  bool addSortedItem( const string &str );
  SortedSeq();
  SortedSeq( const char *str );
};

// using insertion sort algorithm to sort items
void SortedSeq::sort() {
  string tmp;
  int i, j;
  for ( i = 0; i < last; i++ ) {
    tmp = s[ i+1 ];
    for ( j = i; j >= 0 && tmp < s[ j ]; j-- ) {
	s[ j+1 ] = s[ j ];
    }
    s[ j+1 ] = tmp;
  }
}

bool SortedSeq::addSortedItem( const string &str ) {
  int i;
  for ( i = 0; i <= last && str > s[ i ]; i++ )
    ;
  return addItem( i, str );
}

SortedSeq::SortedSeq( const char *fname ) : Sequence( fname ) {
  sort();
}

#endif
