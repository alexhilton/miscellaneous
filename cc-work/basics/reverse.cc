/*
 * reverse.cc
 * reverse a string without using strlen.
 */
#include <iostream>
using namespace std;

char reverse( char str[] ) {
  if ( *str != '\0' ) {
    cout << reverse( ++str );
    return *str;;
  } else {
    return ' ';
  }
}

int main() {
  char *str = new char[ 20 ];
  cout << "input a string: " << endl;
  cin >> str;
  cout << reverse( str );
  delete []str;
  return 0;
}
