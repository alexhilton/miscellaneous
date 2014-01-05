/*
 * lineinput.cc
 * read strings line by line.
 */
#include <iostream>
#include <string>
using namespace std;

int main() {
  char line[ 128 ];
  cout << "input a line of strings: " << endl;
  //cin.getline( line, sizeof( line ) );
  //getline( line, sizeof( line ) );
  cin.get( line, sizeof( line ) );
  cout<< "your inupt is: " << endl;
  cout << line << endl;
  return 0;
}
