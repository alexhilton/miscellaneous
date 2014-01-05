/*
 * set.cc
 * implementation of set data structure.
 */
#include <iostream>
using namespace std;

class Set {
private:
  int *a;
  int size;
  int cursor;
public:
  Set() {;}
  Set( int &s ) {
    size = s;
    a = new int[ size ];
    cursor = 0;
  }
  ~Set() {
    delete []a;
  }
  void setSize( int &s ) {
    size = s;
  }
  int getSize() {
    return size;
  }
  void add( int &elem ) {
    if ( find( elem ) == -1 ) {
      a[ cursor++ ] = elem;
    }
  }
  int get( int &index ) {
    if ( index >= cursor ) {
      cerr << "out of boundary" << endl;
    }
    return a[ index ];
  }
  void remove( int &elem ) {
    int i;
    i = find( elem );
    if ( i != -1 ) {
      for ( ; i < cursor-1; i++ ) {
	a[ i ] = a[ i+1 ];
      }
      cursor--;
    }
  }
  int find( int &elem ) {
    int i;
    for ( i = 0; i < cursor; i++ ) {
      if ( elem == a[ i ] ) {
	return i;
      }
    }
    return -1;
  }
  Set intersection( Set &another ) {
    Set res( size );
    int i;
    for ( i = 0; i < cursor; i++ ) {
      if ( another.find( a[i] ) != -1 ) {
	res.add( a[i] );
      }
    }
    return res;
  }
  Set unionSet( Set &another ) {
    int newSize = size + another.getSize();
    Set res( newSize );
    int i;
    for ( i = 0; i < cursor; i++ ) {
      res.add( a[i] );
    }
    for ( i = 0; i < another.cursor; i++ ) {
      newSize = another.get( i );
      if ( find( newSize ) == -1 ) {
	res.add( newSize );
      }
    }
    return res;
  }
  Set difference( Set &another ) {
    Set res( size );
    int i;
    for ( i = 0; i < cursor; i++ ) {
      if ( another.find( a[i] ) == -1 ) {
	res.add( a[ i ] );
      }
    }
    return res;
  }
  void enumerate() {
    for ( int i = 0; i < cursor; i++ ) {
      cout << a[ i ] << " ";
    }
    cout << endl;
  }
};

int main() {
  int size = 10, i, j, k;
  Set one( size ), two( size ), three;
  for ( i = 0; i < size/2; i++ ) {
    one.add( i );
  }
  j = i + 3;
  one.add( j );
  one.remove( j );
  for ( ; i < size; i++ ) {
    two.add( i );
  }
  k = i - 6;
  two.add( k );
  cout << "Set one" << endl;
  one.enumerate();
  cout << "Set two" << endl;
  two.enumerate();
  three = one.intersection( two );
  cout << "three intersection " << endl;
  three.enumerate();
  three = one.unionSet( two );
  cout << "three union: " << endl;
  three.enumerate();
  three = one.difference( two );
  cout << "three difference of one from two: " << endl;
  three.enumerate();
  return 0;
}
