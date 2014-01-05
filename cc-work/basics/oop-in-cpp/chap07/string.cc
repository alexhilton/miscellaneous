/*
 * string.cc
 *
 * STL container string
 */
/*
 * string.cc
 *
 * this program can not pass g++ compilation.
 * But it can run correctly in Visual C++ compiler.
 */
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

void printChar( char ch ) {
  cout << ch;
}

int main() {
  string s = "pele, the greatest ever";
  // print in original order and reverse
  cout << "s:                " << s << endl;
  cout << "s in reverse: ";
  for_each( s.rbegin(), s.rend(), printChar )
    ;
  cout << endl;

  // find the char 'a'
  char *where = find( s.begin(), s.end(), 'a' );
  cout << "'a' is the " << where - s.begin() + 1 <<"th character in the:'"
       << s << "'" << endl;

  // randomly shuffle the string
  random_shuffle( s.begin(), s.end() );
  cout << "s after a random shuffle: " << s << endl;
  // find 'a' again
  where = find( s.begin(), s.end(), 'a' );
  cout << "'a' is the " << where-s.begin()+1 << "th char in the: '" 
       << s << "'" << endl;
  // sort the string in ascending order
  sort( s.begin(), s.end() );
  cout << "s sorted in ascending order: " << s << endl;
  return 0;
}
