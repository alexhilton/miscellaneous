/*
 * this program show the basic operations on vector container.
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
  //creat an integer vector containing ten zeros.
  vector<int> ivec( 10, 0 ); 
  cout << "size of vector is " << ivec.size();
  ivec.push_back( 5 );
  int i;
  for ( i = 1; i != ivec.size(); i++ ) {
    cout << ivec[ i ] << " ";
  }
  cout << endl;
  return 0;
}
