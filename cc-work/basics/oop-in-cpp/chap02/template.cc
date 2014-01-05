/*
 * template.cc
 * trying template.cc
 * swap is reserved keyword.
 */
#include <iostream>
using namespace std;

template <class Type>
void exchange( Type &s, Type &t );

int main() {
  int a, b;
  float x, y;
  double m, n;
  char p, q;
  cout << " integer " << endl;
  cin >> a >> b;
  exchange( a, b );
  cout << a << " " << b << endl;
  //floating point.
  cout << "floating " << endl;
  cin >> x >> y;
  exchange( x, y );
  cout << x << " " << y << endl;
  //double 
  cout << "double" << endl;
  cin >> m >> n;
  exchange( m, n );
  cout << m << " " << n << endl;
  //character
  cout << "character " << endl;
  cin >> p >> q;
  exchange( p, q );
  cout << p << " " << q << endl;
  return 0;
}

template <class Type>
void exchange( Type &s,  Type &t ) {
  s -= t;
  t += s;
  s = t - s;
}
