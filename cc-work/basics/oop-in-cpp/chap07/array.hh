/*
 * array.hh
 *
 * implement template class Array to be able to resize automatically.
 */
#ifndef _array_hh
#define _array_hh "array.hh"

#include <iostream>
using namespace std;

template< class T >
class Array {
private:
  T *array;
  int size;
  int tail;
  void extend() {
    size *= 2;
    resize();
  }
  void resize() {
    T *tmp = new T[ size ];
    int i;
    for ( i = 0; i <= tail; i++ ) {
      tmp[ i ] = array[ i ];
    }
    delete [ ] array;
    array = tmp;
  }
  bool full() {
    return tail >= size;
  }
  void init() {
    int i;
    for ( i = 0; i < size; i++ ) {
      array[ i ] = 0;
    }
  }
public:
  Array();
  Array( int s );
  ~Array();
  int getSize() const;
  int length() const;
  void setSize( int s );
  T *begin() const;
  T *end() const;
  void insert( T &e );
  void insert( T *p, T &e );
  T operator[ ]( int i ) const;
};

template< class T >
Array< T >::Array() {
  size = 100;
  array = new T[ size ];
  init();
  tail = 0;
}

template< class T >
Array< T >::Array( int s ) {
  array = new T[ size = s ];
  init();
  tail = 0;
}

template< class T >
Array< T >::~Array() {
  delete [ ] array;
}

template< class T >
int Array< T >::getSize() const {
  return size;
}

template< class T >
int Array< T >::length() const {
  return tail;
}

template< class T >
void Array< T >::setSize( int s ) {
  size = s;
  if ( full() ) {
    cerr << "small size" << endl;
    exit( EXIT_FAILURE );
  }
  resize();
}

template< class T >
T* Array< T >::begin() const {
  return array;
}

template< class T >
T* Array< T >::end() const {
  return array + tail;
}

template< class T >
void Array< T >::insert( T &e ) {
  if ( full() ) {
    extend();
  }
  array[ tail++ ] = e;
}

template< class T >
void Array< T >::insert( T *p, T &e ) {
  if ( full() ) {
    extend();
  }
  if ( p < begin() ) {
    p = begin();
  }
  if ( p > end() ) {
    p = end();
  }
  T *tmp = end() + 1;
  for ( ; tmp > p; tmp-- ) {
    *tmp = *( tmp - 1 );
  }
  *tmp = *p;
  tail++;
}

template< class T >
T Array< T >::operator[ ]( int i ) const {
  if ( i < 0 ) {
    i = 0;
  }
  if ( i >= tail ) {
    i = tail - 1;
  }
  return array[ i ];
} 

#endif



