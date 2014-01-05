/*
 * arraydriver.cc
 *
 * a test client for interface array.hh
 */
#include "array.hh"
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void dump( int i ) {
  cout << i << " ";
}

int main() {
  Array< int > a( 10 );
  cout << "check the intializing" << endl;
  int i;
  for ( i = 0; i < a.getSize(); i++ ) {
    dump( a[ i ] );
  }
  cout << endl;

  srand( time( 0 ) );
  // now inserting something
  cout << "now the length is : " << a.length() << endl;
  int tmp;
  for ( i = 0; i < a.getSize(); i++ ) {
    tmp = rand();
    a.insert( tmp );
  }
  cout << "after inserting..." << endl;
  for_each( a.begin(), a.end(), dump );
  cout << endl << "now the length is: " << a.length() << endl;

  // sort it
  sort( a.begin(), a.end() );
  cout << "after sorting the current contents..." << endl;
  for ( i = 0; i < a.length(); i++ ) {
    dump( a[ i ] );
  }
  cout << endl;

  // insert more
  for ( i = 0; i < 5; i++ ) {
    tmp = rand();
    a.insert( a.begin(), tmp );
    tmp = rand();
    a.insert( a.end(), tmp );
  }
  // check current contents
  cout << "the current contents are...: " << endl;
  for_each( a.begin(), a.end(), dump );
  cout << endl;
  cout << "now the length is: " << a.length() << endl;
  cout << "and the size is : " << a.getSize() << endl;
  return 0;
}
