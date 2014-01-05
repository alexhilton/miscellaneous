/*
 * exception.cc
 * try, catch, and throw exerciese.
 * there is a bug in this program, compile error.
 */
#include <iostream>
#include <string>
#include <exception>
using namespace std;

int main() {
  string s;
  int index, len;
  // process string s
  while ( true ) {
    cout << "Enter index and length to erase: ";
    cin >> index >> len;
    try {
      // code that might raises an exception.
      s.erase( index, len );
    } 
    catch ( out_of_range ) {
      continue;
    }
    break;
  }
  return 0;
}
