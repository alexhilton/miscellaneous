/*
 * stloutput.cc
 *
 * STL output iterator
 * fstream
 * ostream_iterator
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  // poppulate vector with first 32 fibonacci numbers
  vector< int > fib( 32 );
  fib[ 0 ] = fib[ 1 ] = 1; // base case
  int i;
  for ( i = 2; i < 32; i++ ) {
    fib[ i ] = fib[ i-1 ] + fib[ i-2 ];
  }
  // create output stream and iterator
  ofstream out( "output.dat" );
  ostream_iterator< int > outit( out, " " );
  ostream_iterator< int >stdoutit( cout, "\n" );
  // copy output file and to standard otuput.
  copy( fib.begin(), fib.end(), outit );
  copy( fib.begin(), fib.end(), stdoutit );
  return 0;
}
