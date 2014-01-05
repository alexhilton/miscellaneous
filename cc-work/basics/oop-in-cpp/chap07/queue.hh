/*
 * queue.cc
 *
 * implement data structure queue whose element is First In First Out
 * FIFO.
 */
#ifndef _queue_hh
#define _queue_hh "queue.hh"
#include <iostream>
using namespace std;

template< class T >
class Queue {
private:
  T *elem;
  int head;
  int tail;
  int size;
public:
  Queue();
  Queue( int s );
  ~Queue();
  int getSize() const;
  void extend( int s );
  T pop();
  void push( const T &elem );
  T top();
  bool empty() const;
  bool full() const;
  T *begin() const;
  T *end() const;
};

template< class T >
Queue< T >::Queue() {
  size = 50;
  elem = new T[ 50 ];
  head = tail = 0;
}

template< class T >
Queue< T >::Queue( int s ) {
  elem = new T[ size = s ];
  head = tail = 0;
}

template< class T >
Queue< T >::~Queue() {
  delete [ ] elem;
}

template< class T >
int Queue< T >::getSize() const {
  return size;
}

template< class T >
void Queue< T >::extend( int s ) {
  if ( s < size ) {
    cerr << "Small Size!" << endl;
    exit( EXIT_FAILURE );
  }
  T *tmp = new T[ s ];
  int i, j;
  for ( j = 0, i = head; i  < tail; i++, j++ ) {
    tmp[ j ] = elem[ i%size ];
  }
  delete [ ] elem;
  elem = tmp;
  size = s;
  head = 0;
  tail = j - 1;
}

template< class T >
T Queue< T >::pop() {
  T tmp = T();
  if ( !empty() ) {
    tmp = elem[ head ];
    head = ( head + 1 ) % size;
  } else {
    cerr << "Queue is empty!" << endl;
  }
  return tmp;
}

template< class T >
void Queue< T >::push( const T &e ) {
  if ( !full() ) {
    tail = ( tail + 1 ) % size;
    elem[ tail ] = e;
  } else {
    cerr << "Queue is full!" << endl;
    exit( EXIT_FAILURE );
  }
}

template< class T >
T Queue< T >::top() {
  if ( !empty() ) {
    return elem[ head ];
  } else {
    cerr << "Queue is full!" << endl;
    exit( EXIT_FAILURE );
  }
}

template< class T >
bool Queue< T >::empty() const {
  if ( head == tail ) {
    return true;
  }
  return false;
}

template< class T >
bool Queue< T >::full() const {
  if ( ( tail + 1 ) % size == head ) {
    return true;
  }
  return false;
}

template< class T >
T* Queue< T >::begin() const {
  return elem + head;
}

template< class T >
T* Queue< T >::end() const {
  return elem + tail;
}

#endif
