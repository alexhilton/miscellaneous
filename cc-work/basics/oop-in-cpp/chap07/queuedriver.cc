/*
 * queuedriver.cc
 *
 * queue.hh interface test driver.
 */
#include "queue.hh"
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void dump( int i ) {
  cout << i << " ";
}

int main() {
  Queue< int > q( 20 );
  int size = 20;
  int i;
  srand( time( 0 ) );
  for ( i = 0; i < size/2; i++ ) {
    q.push( rand() );
  }

  // check the queue
  for_each( q.begin(), q.end(), dump );
  cout << endl;
  cout << "the size is " << q.getSize() << endl;

  // enlarge the queue
  size *= 2;
  q.extend( size );
  for ( i = 0; i < size/2; i++ ) {
    q.push( rand() );
  }

  // check the value
  for_each( q.begin(), q.end(), dump );
  cout << endl;

  cout << "now the size is " << q.getSize() << endl;
  // sorting in ascending order
  sort( q.begin(), q.end() );
  cout << "before sorting..." << endl;
  cout << "after sorting..." << endl;
  // check the queue
  while ( !q.empty() ) {
    dump( q.pop() );
  }
  cout << endl;

  return 0;
}
