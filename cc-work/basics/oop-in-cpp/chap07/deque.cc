/*
 * deque.cc
 *
 *  container deque at a first glance
 */
#include <iostream>
#include <deque>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
  unsigned i;
  deque< int > num;

  unsigned size = 10;
  num.insert( num.begin(), -999 );
  num.insert( num.begin(), 14 );
  num.insert( num.end(), 57 );

  for ( i = 0; i < num.size(); i++ ) {
    cout << num[ i ] << endl;
  }
  cout << endl;

  num.erase( num.begin() );
  num.erase( num.begin() );
  num.insert( num.end(), 20 );

  for ( i = 0; i < num.size(); i++ ) {
    cout << num[ i ] << endl;
  }
  cout << endl;
  // test sorting algo
  //
  for ( i = 0; i < size/2; i++ ) {
    num.insert( num.begin(), rand() % 100 );
  }
  for ( ; i < size; i++ ) {
    num.insert( num.end(), rand() % 100 );
  }

  sort( num.begin(), num.end() );
  for ( i = 0; i < num.size(); i++ ) {
    cout << num[ i ] << " ";
  }
  cout << endl;
  return 0;
}
