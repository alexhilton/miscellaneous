/*
 * calend.cc
 * write a code that output a month in the form of calendar.
 */
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
  int day = 2;
  int i;
  cout << setw( 5 ) << ' ';
  cout << setw( 5 ) << ' ';
  for ( i = 1; i <= 31; i++ ) {
    if ( day % 7 == 0 ) {
      cout << endl;
    }
    cout << setw( 5 ) << i;
    day++;
  }
  cout << endl;
  return 0;
}
