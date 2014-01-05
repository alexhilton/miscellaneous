/*
 * overload.cc
 * demostrate how to use function overloading.
 */
#include <iostream>
using namespace std;

/* square function for int, float and double */
int square( int x );
float square( float x );
double square( double x );

int main() {
  int x;
  float y;
  double z;
  cout << "?: ";
  cin >> x;
  cout << " integer " << square( x ) << endl;
  cout << "?: ";
  cin >> y;
  cout << " float " << square( y ) << endl;
  cout << "?: ";
  cin >> z;
  cout << "double " << square( z ) << endl;
  return 0;
}

int square( int x ) {
  return x * x;
}

float square( float y ) {
  return y * y;
}

double square( double z ) {
  return z * z;
}
