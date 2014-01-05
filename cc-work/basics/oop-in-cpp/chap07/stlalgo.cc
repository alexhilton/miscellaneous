/*
 * stlalgo.cc
 *
 * STL algorithms at first glance
 * generate
 * sort 
 * for_each
 */
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

void dump( int i ) {
  cout << i << endl;
}

bool odd( int i ) {
  return ( i & 0x01 ) != 0;
}

bool cmp( const int &a, const int &b ) {
  return a > b;
}

int main() {
  vector< int > v( 10 ); // vector of 10 integer
  // fill with random integers
  generate( v.begin(), v.end(), rand );
  // replace odds with 0
  replace_if( v.begin(), v.end(), odd, 0 );
  // sort in descending order
  sort( v.begin(), v.end(), cmp );
  for_each( v.begin(), v.end(), dump );
  // sort in ascending order
  cout << "sorting in ascending order" << endl;
  sort( v.begin(), v.end() ); // last cmp is optional
  for_each( v.begin(), v.end(), dump );
  return 0;
}
