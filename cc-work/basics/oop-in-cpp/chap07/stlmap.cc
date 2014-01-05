/*
 * stlmap.cc
 *
 * STL map at a first glance
 */
#include <map>
#include <iostream>
#include <string>
using namespace std;

int main() {
  map< string, int > m1;
  m1[ "zero" ] = 0;
  m1[ "one" ] = 1;
  m1[ "two" ] = 2;
  m1[ "three" ] = 3;
  m1[ "four" ] = 4;
  m1[ "five" ] = 5;
  m1[ "six" ] = 6;
  m1[ "seven" ] = 7;
  m1[ "eight" ] = 8;
  m1[ "nine" ] = 9;

  cout << m1[ "three" ] << endl; //  3
  cout << m1[ "five" ] << endl; // 5
  cout << m1[ "seven" ] << endl;

  // another taste
  map< string, string > m2;
  m2[ "Gates" ] = "Microsoft";
  m2[ "Jobs" ] = "Apple";
  m2[ "Ellison" ] = "Oracle";

  cout << m2[ "Gates" ] << endl;
  cout << m2[ "Jobs" ] << endl;
  cout << m2[ "Ellison" ] << endl;

  return 0;
}
