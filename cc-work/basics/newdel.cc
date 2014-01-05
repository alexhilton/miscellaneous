/*
 * newdel.cc
 * demostration of new and delete to create array and 
 * destroy array.
 */
#include <iostream>
using namespace std;

int main() {
  int *a = new int[ 10 ]; // create an integer array with 10 elements.
  int *b = new int; // allocate memory for b pointer
  cout << "input an integer: ";
  //scanf( "%d", b );
  cin >> *b;
  cout << "b = " << *b << endl;
  delete b; // free memory allocated for b
  int i;
  for ( i = 0; i < 10; i++ ) {
    a[ i ] = i+1;
    cout << a[ i ] << " ";
  }
  cout << endl;
  //cout << "*a == a[ 0 ] ??, try it, *a = " << *a << ", and a[0] = " << a[ 0 ] << endl;
  //if int *a = new int[10], then *a = a[ 0 ];
  delete []a; // free memory for array a.
  return 0;
}
