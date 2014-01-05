/*
 * inline.cc
 * exercises for inline function definition and using,
 * inline function is more secure than macro, it can prevent
 * side effects caused by increment and decrement operators.
 * but a good programming convention should avoid both of them.
 */
#include <iostream>
using namespace std;
#define SQUARE( X ) (X)*(X)
inline double square( double x ) { return (x)*(x); }

int main() {
  double x;
  cout << "input a value: ";
  cin >> x;
  /*
   * inline is more secure, it will evaluate value of
   * argument before insert function into caller.
   */
  cout << "square of it is: " << square(x) << endl;
  cout << "square of increment is: " << square( ++x ) << endl;
  cout << "using macro: " << endl;
  /*
   * where macro is different, it just replace target with macro
   * so, you put what in parethesis, it will replace what in macro.
   */
  cin >> x;
  cout << SQUARE( x ) << endl;
  cout << "increment " << SQUARE( ++x ) << endl;
  //what is different
  cin >> x;
  cout << SQUARE(x) << " "  << SQUARE( ++x ) << endl;
  // output is 36, 30 if input x is 4;
  // after replacement it looks like:
  // cout << x*x << (++x)*(++x) << endl;
  // cout << 6*6 << 5*6 << endl;
  // it seems that cout process from rear to front.
  return 0;
}
