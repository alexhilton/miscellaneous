/*
 * lightyear.cc
 * a program to translate lightyear into kilometers.
 */
#include <iostream>
using namespace std;

double tran( double light ) {
  const double auperl = 63240;
  return light * auperl;
}

int main() {
  double light;
  cout << "Enter the number of light years: ";
  cin >> light;
  cout << light << " light years are " << tran( light ) << " astronomical units." << endl;
  return 0;
}
