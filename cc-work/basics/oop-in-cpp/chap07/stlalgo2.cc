/*
 * stlalgo2.cc
 *
 * STL algorithms at a second glance
 * random_shuffle
 * nth_element
 * copy
 ***** again this program cannot pass g++ compilation, but it can
 * go smoothly in Visual C++
 */
#include <iostream>
#include <algorithm>
using namespace std;

void print( const char *s, char a[ ], int i );

void dump( char ch ) {
  cout << ch;
}

int main() {
  const int len = 27;
  const int med = len / 2;

  // print a sorted array of 27 nonduplicate character
  char alpha[ ] = "abcdefghijklmnopqrstuvwxyz{"; // 27
  print( "\n\nOriginal array:\n", alpha, len );

  // shuffle the array and print it
  random_shuffle( alpha, alpha + len ); // shuffle the chars
  print( "\n\nAfter random_shuffle:\n", alpha, len );

  // arrange the array's elements so that the array cell
  // alpha[ med ] holds the median character: all characters
  // less than alpha[ med ] are to its left; all characters
  // greater than alpha[ med ] are to its rigth.
  nth_element( alpha, alpha + med, alpha + len );
  print( "\n\nAfter nth_element:\n", alpha, len );
  print( "\n\t < median: ", alpha, med );
  print( "\n\t   median: ", alpha + med, 1 );
  print( "\n\t > median: ", alpha + med + 1, len / 2 );
  cout << endl;
  return 0;
}

void print( const char *msg, char a[ ], int len ) {
  cout << msg;
  //copy( a, a + len, ostream_iterator< char >( cout, " " ) );
  for_each( a, a+len+1, dump );
}
