/*
 * output2.cc
 * practice setw.
 * setfill
 * setprecision
 * left and right-justify
 */
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  int i;
  for ( i = 1; i <= 1000; i *= 10 ) {
    cout << setw( 6 ) << i << endl;
  }
  cout << endl;
  // once the setfill is set, it remains in effect until it
  // is changed.
  cout << setfill( '*' );
  for ( i = 1; i <= 1000; i *= 10 ) {
    cout << setw( 6 ) << i << endl;
  }
  cout << endl;

  // about setprecision
  // once the setprecision is set, it remains in effect until
  // it is changed.
  float a = 1.05, b = 10.15, c = 200.87;
  cout << setfill( '*' ) << setprecision( 2 );
  cout << setw( 10 ) << a << endl;
  cout << setw( 10 ) << b << endl;
  cout << setw( 10 ) << c << endl;

  // left and right-justify.
  int a1 = 5, b1 = 43, c1 = 104;
  cout << endl;
  cout << setfill( ' ' );
  cout << left << setw( 10 ) << "Karen"
    << right << setw( 6 ) << a1 << endl;
  cout << left << setw( 10 ) << "Ben" 
    << right << setw( 6 ) << b1 << endl;
  cout << left << setw( 10 ) << "Patricia"
    << right << setw( 6 ) << c1 << endl;

  // showpoint, fixed
  a = 5;
  b = 43.3;
  c = 10304.31;
  cout << endl;
  cout << showpoint << fixed << setprecision( 2 );
  cout << setw( 8 ) << a << endl;
  cout << setw( 8 ) << b << endl;
  cout << setw( 8 ) << c << endl;

  // if showpoint and fixed are not used.
  cout << endl;
  cout << "showpoint and fixed are not used" << endl;
  cout << setw( 8 ) << a << endl;
  cout << setw( 8 ) << b << endl;
  cout << setw( 8 ) << c << endl;

  // concel the showpoint effect
  cout << noshowpoint; 
  cout << setw( 8 ) << a << endl;
  cout << setw( 8 ) << c << endl;
  return 0;
}
