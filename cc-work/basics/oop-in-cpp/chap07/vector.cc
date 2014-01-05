/*
 * vector.cc
 *
 *  container vector at a first glance
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
  unsigned i;
  vector< int > num;

  int size = 10;
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
  // test sort algo

  for ( i = 0; i < size; i++ ) {
    num.insert( num.end(), rand() % 100 );
  }
  sort( num.begin(), num.end() );

  for ( i = 0; i < num.size(); i++ ) {
    cout << num[ i ] << " ";
  }
  cout << endl;
  return 0;
}
