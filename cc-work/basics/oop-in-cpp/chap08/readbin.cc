/*
 * readbin.cc
 *
 * try to read a binary file
 */
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

int main() {
  ifstream in;
  string filename;
  cout << "input filename: ";
  cin >> filename;
  in.open( filename.c_str(), ios_base::binary );
  int n;
  if ( in ) {
    while ( in >> n ) {
        cout << n;
    }
    cout << endl;
    in.close();
  }
  cout << endl;
  return 0;
}
