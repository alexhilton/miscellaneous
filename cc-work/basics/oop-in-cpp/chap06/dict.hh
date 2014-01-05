/*
 * dict.hh
 *
 * a class array.hh
 */
#include <string>
#include <iostream>
using namespace std;

#define MAX_SIZE 100

class Entry {
private:
  string word;
  string def;
  bool flag;
public:
  Entry() { flag = false; }
  void add( const string &w, const string &d );
  bool match( const string &w ) const;
  void operator=( const string &w );
  void operator=( const char *w );
  friend ostream &operator<<( ostream &out, const Entry &ent );
  bool valid() const { return flag; }
};

void Entry::operator=( const string &str ) {
  def = str;
  flag = true;
}

void Entry::operator=( const char *str ) {
  def = str;
  flag = true;
}

ostream &operator<<( ostream &out, const Entry &ent ) {
  out << endl << ent.word << " defined as: " << ent.def;
  return out;
}

void Entry::add( const string &w, const string &d ) {
  word = w;
  def = d;
}

bool Entry::match( const string &key ) const {
  return key == word;
}

// deriv class
class Dict {
private:
  Entry entries[ MAX_SIZE + 1 ];
public:
  friend ostream &operator<<( ostream &out, const Dict &dict );
  Entry &operator[]( const string &w );
  Entry &operator[]( const char *w );
};

ostream &operator<<( ostream &out, const Dict &dict ) {
  int i;
  for ( i = 0; i < MAX_SIZE; i++ ) {
    if ( dict.entries[ i ].valid() ) {
      out << dict.entries[ i ];
    }
  }
  return out;
}

// this overloading is searching k
Entry &Dict::operator[]( const string &k ) {
  int i;
  for ( i = 0; i < MAX_SIZE && entries[i].valid(); i++ ) {
    if ( entries[ i ].match( k ) ) {
      return entries[ i ];
    }
  }
  string not_found = "*** not in dictionary ***";
  entries[ i ].add( k, not_found );
  return entries[ i ];
}

// this is also searching for k, but k is different type
Entry &Dict::operator[]( const char *k ) {
  string s = k;
  return operator[]( s );
}
