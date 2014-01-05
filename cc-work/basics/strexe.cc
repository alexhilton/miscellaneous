#include <iostream>
using namespace std;

int main() {
  string str;
  cout << "input a string:" << endl;
  getline( cin, str );
  cout << "the string you've just input is: " << str << endl;
  cout << "the size of this string is: " << str.size() << endl;
  cout << str.substr( 2, 5 ) << endl;
  cout << "the upper form of it: " << endl;
  return 0;
}
