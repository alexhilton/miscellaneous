/*
 * swapf.cc
 * swap floating point with bitwise operation.
 */
#include <iostream>
using namespace std;

int main() {
  int a, b;
  float x, y;
  cout << "integer catogery: " << endl;
  cout << "? ?: ";
  cin >> a >> b;
  // swapping two variables
  // apply for integer only
  a ^= b;
  b ^= a;
  a ^= b;
  cout << " a = " << a << " b = " << b << endl;

  // swapping two floating points.
  // actually, it applies to any type
  cout << "floating points catogery: " << endl;
  cout << "? ?: ";
  cin >> x >> y;
  x -= y;
  y += x;
  x = y - x;
  cout << "x = " << x << " y = " << y << endl;

  // swapping, another way.
  x = x+y;
  y = x - y;
  x = x - y;
  cout << "x = " << x << " y = " << y << endl;
  return 0;
}
