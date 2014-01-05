/*
 * priority queue.c
 *
 * STL adaptor priority_queue at a first glance
 */
#include <iostream>
#include <functional>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
  const int HOW_MANY = 8; // priority_queue size
  int i;
  priority_queue< int > num;
  srand( time( 0 ) );

  for ( i = 0; i < HOW_MANY; i++ ) {
    int next = rand();
    cout << next << endl;
    num.push( next );
  }

  cout << endl << "*** priority queue by value" << endl;
  for ( i = 0; i < HOW_MANY; i++ ) {
    cout << num.top() << endl;
    num.pop();
  }
  return 0;
}
