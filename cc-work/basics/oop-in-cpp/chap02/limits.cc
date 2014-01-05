/*
 * limits.cc
 * check out the upper and lower limits of built-in types.
 */
#include <iostream>
#include <climits>
using namespace std;

int main() {
  int n_int = INT_MAX;
  short n_short = SHRT_MAX;
  long n_long = LONG_MAX;

  // use sizeof operator yields size of type or of variable.
  cout << "int is " << sizeof( int ) << " bytes." << endl;
  cout << "short is " << sizeof( n_short ) << " bytes " << endl;
  cout << "long is " << sizeof( n_long ) << " bytes." << endl;

  cout << "maximum values: " << endl;
  cout << "int: " << n_int << endl;
  cout << "short: " << n_short << endl;
  cout << "long: " << n_long << endl;
  return 0;
}
