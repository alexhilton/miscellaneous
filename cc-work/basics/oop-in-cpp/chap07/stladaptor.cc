/*
 * stladaptor.cc
 *
 * count_if
 * even
 * not1
 * this program can not compiled and run with g++.
 * it go smoothly in Visual C++
 */
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

struct even : public unary_function< unsigned, bool > {
  bool opeartor()( unsigned n ) const {
    return n % 2 == 0;
  }
};

int main() {
  int a[ ] = { 1, 2, 3, 4, 5 };
  int n;
  n = count_if( a, a + 5, even() );
  cout << "a has " << n << " even integers." << endl;
  n = count_if( a, a + 5, not1( even() ) );
  cout << " a has " << n << " odd integers." << endl;
  return 0;
}	     
