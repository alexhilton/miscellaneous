/*
 * template array.
 */
#include <iostream>
using namespace std;

template< class T >
class Array {
private:
  T *a;
  int size;
  Array();
  T dummyValue; // return for bad index
public:
  T &operator[]( int n );
  const T &operator[]( int n ) const;
  Array( int n );
  ~Array();
  int getSize() const {
    return size;
  }
};

template< class T >
T &Array< T >::operator[]( int i ) { // searching method
  if ( i < 0 || i >= size ) {
    cerr << "index out of boundary" << endl;
    exit( EXIT_FAILURE );
  }
  return a[ i ];
}

template< class T >
const T &Array< T >::operator[]( int i ) const {
  if ( i < 0 || i >= size ) {
    cerr << "index out of boundary" << endl;
    return dummyValue;
  }
  return a[ i ];
}

template< class T >
Array< T >::Array( int n ) {
  a = new T[ size = n ];
}

template< class T >
Array< T >::~Array() {
  delete [] a;
}

// top-level overload of operator <<
template< class T >
ostream &operator<<( ostream &out, const Array< T > &ar ) {
  for ( int i = 0; i < ar.getSize(); i++ ) {
    out << ar[ i ] << endl;
  }
  return out;
}

int main() {
  Array< int > a( 10 ); // integer array, size is 10
  int i;
  for ( i = 0; i < 10; i++ ) {
    a[ i ] = i;
  }
  cout << endl;
  for ( i = 0; i < 10; i++ ) {
    cout << a[ i ] << " ";
  }
  cout << endl;
  return 0;
}
