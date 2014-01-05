/*
 * usercopy.cc
 *
 * a sample demonstrates how to use user defined copy constructor
 */
#include <iostream>
#include <string>
using namespace std;

class NameList {
private:
  int size;
  string *p;
  void copyIntop( const NameList & );
public:
  NameList() { size = 0; p = NULL; }
  NameList( const string [], int );
  NameList( const NameList & );
  void set ( const string &, int );
  void set( const char *, int );
  void dump() const;
};
NameList::NameList( const string s[], int si ) {
  size = si;
  p = new string[ size ];
  int i;
  for ( i = 0; i < size; i++ ) {
    p[ i ] = s[ i ];
  }
}

NameList::NameList( const NameList &d ) {
  p = NULL;
  copyIntop( d );
}

void NameList::copyIntop( const NameList &n ) {
  int i;
  delete [] p;
  if ( n.p != NULL ) {
    p = new string[ size = n.size ];
    for ( i = 0; i < size; i++ ) {
      p[ i ] = n.p[ i ];
    }
  } else {
    p = NULL;
    size = 0;
  }
}

void NameList::set( const string &s, int i ) {
  p[ i ] = s;
}

void NameList::set( const char *s, int i ) {
  p[ i ] = s;
}

void NameList::dump() const {
  int i;
  for ( i = 0; i < size; i++ ) {
    cout << p[ i ] << endl;
  }
  cout << endl;
}

int main() {
  string list[] = { "Lab", "Husky", "Collie" };
  NameList d1( list, 3 );
  d1.dump(); // Lab, Husky, Collie
  // compiler version copy constructor
  NameList d2( d1 );
  d2.dump(); // Lab, Husky, Collie
  d2.set( "Great Dane", 1 );
  d2.dump(); // Lab, Great Dane, Collie
  d1.dump(); // Lab, Great Dane, Collie

  return 0;
}
