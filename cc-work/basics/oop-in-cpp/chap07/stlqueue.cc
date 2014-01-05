/*
 * stlqueue.c
 *
 * STL adaptor queue at a first glance
 */
#include <iostream>
#include <queue>
using namespace std;

int main() {
  queue< int > q; // equals to queue< int, deque< int > > q
  q.push( 1 ); // enqueue actually speaking
  q.push( 2 );
  q.push( 0 );
  q.push( 4 );
  while ( !q.empty() ) {
    cout << q.front() << endl;
    q.pop();
  }
  return 0;
}
