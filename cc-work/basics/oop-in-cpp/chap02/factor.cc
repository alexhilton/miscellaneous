/*
 * factor.cc
 * find out factorial of first ten number, up to 10.
 */
#include <iostream>
using namespace std;

int main() {
  double fact = 1;
  int i;
  for ( i = 1; i <= 10; i++ ) {
    fact *= (double) i;
    cout << i << "! = " << fact << endl;
  }
  return 0;
}
