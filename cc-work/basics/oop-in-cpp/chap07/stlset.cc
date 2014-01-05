/*
 * set.cc
 *
 * container set at a first glance
 */
#include <set>
#include <iostream>
using namespace std;

int main() {
  set< int > s;
  s.insert( -999 ); // insert somewhere
  s.insert( s.begin(), 100 ); // insert at front
  s.insert( s.end(), 20 ); // insert at rear
  s.insert( 321 );
  // since set is unordered, non-duplicated collection, so
  // insert at front or at rear does not make so much sense
  s.insert( 234 );
  s.insert( -999 );
  s.insert( 321 );
  set< int >::const_iterator it;
  it = s.begin();
  while ( it != s.end() ) {
    cout << *it++ << " ";
  }
  cout << endl;

  // using find method to find a specified key
  // prompt the user
  int key;
  cout << "enter an integer: ";
  cin >> key;
  it = s.find( key );
  if ( it == s.end() ) {
    cout << "key: " << key << " is not in the set" << endl;
  } else {
    cout << "key: " << key << " is in the set" << endl;
  }

  return 0;
}
