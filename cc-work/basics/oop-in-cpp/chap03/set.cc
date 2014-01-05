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
  Set() { // default constructor
    size = 0; 
    cursor = 0;
    a = NULL;
  }
  Set( const int &s ) {
    size = s;
    a = new int[ size ];
    cursor = 0;
  }
  ~Set() {
    delete []a;
  }
  void setSize( const int &s ) {
    size = s;
  }
  int getSize() {
    return size;
  }
  int getCursor() const {
    return cursor;
  }
  void add( const int &elem ) {
    if ( find( elem ) == -1 ) {
      a[ cursor++ ] = elem;
    }
  }
  int get( const int &index ) {
    if ( index >= cursor ) {
      cerr << "out of boundary" << endl;
    }
    return a[ index ];
  }
  void remove( const int &elem ) {
    int i;
    i = find( elem );
    if ( i != -1 ) {
      for ( ; i < cursor-1; i++ ) {
	a[ i ] = a[ i+1 ];
      }
      cursor--;
    }
  }
  int find( const int &elem ) {
    int i;
    for ( i = 0; i < cursor; i++ ) {
      if ( elem == a[ i ] ) {
	return i;
      }
    }
    return -1;
  }
  void intersection( Set &another ) {
    int i;
    for ( i = 0; i < cursor; i++ ) {
      if ( another.find( a[ i ] ) != -1 ) {
        cout << a[ i ] << " ";
      }
    }
    cout << endl;
  }
  void unionSet( Set &another ) {
    int tmp;
    int i;
    for ( i = 0; i < cursor; i++ ) {
      cout << a[ i ] << " ";
    }
    for ( i = 0; i < another.cursor; i++ ) {
      tmp = another.get( i );
      if ( find( tmp ) == -1 ) {
	cout << tmp << " ";
      }
    }
    cout << endl;
  }
  void difference( Set &another ) {
    int i;
    for ( i = 0; i < cursor; i++ ) {
      if ( another.find( a[i] ) == -1 ) {
	cout << a[ i ] << " ";
      }
    }
    cout << endl;
  }
  void enumerate() {
    cout << "\t";
    for ( int i = 0; i < cursor; i++ ) {
      cout << a[ i ] << " ";
    }
    cout << endl;
  }
};

int main() {
  int size = 10;
  Set one( size ), two( size );
  one.add( 2 );
  one.add( 4 );
  one.add( 5 );
  one.add( 5 );
  one.add( 6 );
  two.add( 9 );
  two.add( 10 );
  two.add( 10 );
  two.add( 2 );
  two.add( 5 );
  cout << "Set one" << endl;
  cout << "\tsize is " << one.getCursor() << endl;
  one.enumerate();
  cout << "Set two" << endl;
  cout << "\tsize is " << two.getCursor() << endl;
  two.enumerate();
  cout << "intersection of one and two " << endl;
  one.intersection( two );
  cout << "union of one and two: " << endl;
  one.unionSet( two );
  cout << "difference of one from two: " << endl;
  one.difference( two );
  cout << "remove 4 from one: " << endl;
  one.remove( 4 );
  one.enumerate();
  return 0;
}
