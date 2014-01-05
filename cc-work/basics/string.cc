/*
 * string.cc
 * a practice of string.
 */
#include <iostream>
#include <string>
using namespace std;

int main() {
  string s1;
  string s2 = "Bravo";
  string s4 = s2;
  string s5( 10, '8' );

  cout << "input a string" << endl;
  getline( cin, s1 );
  cout << s1 << " " << s2 << " " << s4 << " " << s5 << endl;
  cout << s1.length() << endl;
  cout << s1.substr( 3, 7 ) << endl;
  cout << s1.insert( 4, s2 ) << endl;
  cout << s1+s2+s1 << endl;
  int ind;
  s1.find( s2, ind );
  cout << ind << endl;
  bool res = s4 > s2;
  cout << res << endl;
  return 0;
}
