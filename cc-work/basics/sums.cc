/*
 * sums.cc
 * enter ten numbers integer types in any order.
 * output the sums of all the number greater than zero, 
 * less than zero and the sum of ten numbers.
 */
#include <iostream>
using namespace std;

int main() {
  int *a;
  a = new int[ 10 ];
  int sum = 0, psum = 0, nsum = 0;
  int i;
  for ( i = 0; i < 10; i++ ) {
    cout << "?: ";
    cin >> a[ i ];
    if ( a[ i ] > 0 ) {
      psum += a[ i ];
    } else {
      nsum += a[ i ];
    }
    sum += a[ i ];
  }
  cout << endl;
  cout << "Positive numbers' sum: " << psum << endl;
  cout << "Negative numbers' sum: " << nsum << endl;
  cout << "the sum of them: " << sum << endl;
  delete []a;
  return 0;
}
