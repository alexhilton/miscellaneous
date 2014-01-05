/*
 * testing driver for complex.hh
 */
#include <iostream>
#include "complex.hh"
using namespace std;

int main() {
  Complex c1( 7.7f, 5.5f );
  Complex c2( 4.2f, -8.3f );
  Complex c3;

  c3 = c1 + c2;
  cout << "c1 + c2 = ";
  c3.write();

  c3 = c1 - c2;
  cout << "c1 - c2 = ";
  c3.write();

  c3 = c1 * c2;
  cout << "c1 * c2 = ";
  c3.write();

  c3 = c1 / c2;
  cout << "c1 / c2 = ";
  c3.write();

  c3 = ~c1;
  cout << "~c1 = ";
  c3.write();

  double a = !c1;
  cout << "|c1| = ";
  cout << a << endl;

  c3 = -c2;
  cout << "-c2 ";
  cout << c3;

  if ( c1 == c2 ) {
    cout << "c1 == c2" << endl;
  } else {
    cout << "c1 != c2" << endl;
  }

  cout << "input c3 ";
  cin >> c3;
  cout << c3;
  return 0;
}
