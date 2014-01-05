/*
 * queue.cc
 * implementation of a queue.
 */
#include <iostream>
using namespace std;

class Queue {
private:
  int *a;
  int size;
  int head, tail;
public:
  Queue() {;};
  Queue( int &s ) {
    size = s;
    a = new int[ size ];
    head = tail = 0;
  }
  ~Queue() {
    delete []a;
  }
  void setSize( int &s ) {
    size = s;
  }
  int getSize() const {
    return size;
  }
  void enqueue( int elem ) {
    if ( full() ) {
      cerr << "Queue is full!" << endl;
    }
    a[ tail ] = elem;
    tail = (tail+1) % size;
  }
  int dequeue() {
    int tmp;
    if ( empty() ) {
      cerr << "Queue is empty!" << endl;
    }
    tmp = head;
    head = (head+1) % size;
    return a[ tmp ];
  }
  bool empty() {
    if ( head == tail ) {
      return true;
    }
    return false;
  }
  bool full() {
    if ( head > tail ) {
      if ( tail+1 == head ) {
	return true;
      }
    } else {
      if ( head+size == tail+1 ) {
	return true;
      }
    }
    return false;
  }
};

int main() {
  int i, size = 5;
  Queue one;
  Queue two( size );
  for ( i = 0; i < size-1; i++ ) {
    two.enqueue( i );
  }
  for ( i = 0; i < size-1; i++ ) {
    cout << two.dequeue() << " " << endl;
  }
  return 0;
}
