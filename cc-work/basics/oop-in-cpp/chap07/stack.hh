/*
 * stack.hh
 * 
 * Implement template Stack.
 */
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
// enable or disable assertion
// #define NDEBUG
using namespace std;

template< class T >
class Stack {
private:
  T *element;
  int top;
  int size;
  void allocate() {
    element = new T[ size ];
    top = EMPTY_STACK;
  }

  void msg( const char *m ) const {
    cout << "**** " << m << " ****" << endl;
  }

  friend ostream &operator<<( ostream &out, const Stack< T > &s );
public:
  enum { DEFAULT_SIZE = 50, EMPTY_STACK = -1 };
  Stack();
  Stack( int s );
  ~Stack();
  void push( const T &elem );
  T pop();
  T getTop() const;
  bool empty() const;
  bool full() const;
};

template< class T >
Stack< T >::Stack() {
  size = DEFAULT_SIZE;
  allocate();
}

template< class T >
Stack< T >::Stack( int s ) {
  if ( s < 0 ) {
    s *= -1;
  } else if ( s == 0 ) {
    s = DEFAULT_SIZE;
  }
  size = s;
  allocate();
}

template< class T >
Stack< T >::~Stack() {
  delete [ ] element;
}

template< class T >
void Stack< T >::push( const T &elem ) {
  assert( !full() );
  if ( !full() ) {
    element[ ++top ] = elem;
  } else {
    msg( "Stack is full" );
  }
}

template< class T >
T Stack< T >::pop() {
  assert( !empty() );
  if ( !empty() ) {
    return element[ top-- ];
  } else {
    msg( "Stack is Empty" );
    T dummy_value;
    return dummy_value;
  }
}

template< class T >
T Stack< T >::getTop() const {
  assert( top > EMPTY_STACK );
  if ( !empty() ) {
    return element[ top ];
  } else {
    msg( "Stack is empty" );
    T dummy_value;
    return dummy_value;
  }
}

template< class T >
bool Stack< T >::empty() const {
  return top <= EMPTY_STACK;
}

template< class T >
bool Stack< T >::full() const {
  return top+1 >= size;
}

template< class T >
ostream &operator<<( ostream &out, const Stack< T > &s ) {
  s.msg( "Stack contents" );
  int t = s.top;
  while ( t > s.EMPTY_STACK ) {
    cout << s.element[ t-- ] << endl;
  }
  return out;
}
