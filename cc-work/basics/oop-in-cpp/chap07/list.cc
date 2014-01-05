/*
 * list.cc 
 *
 * container list at a first glance
 */
#include <iostream>
#include <list>
#include <string>
using namespace std;

void dump( list< string > &name );

int main() {
  list< string > name;
  // insert four names into a list
  name.insert( name.begin(), "Kamio" );
  name.insert( name.end(), "Hitlion" );
  name.insert( name.begin(), "Kevin" );
  name.insert( name.end(), "Maria" );
  name.insert( name.begin(), "Kate" );
  name.insert( name.end(), "Garnett" );
  name.insert( name.begin(), "Andra" );
  name.insert( name.end(), "Sam" );

  // traverse the name lists
  cout << "traverse the name list: " << endl;
  dump( name );
  // what about reverse it
  cout << "what about reverse it:" << endl;
  name.reverse();
  dump( name );
  cout << endl;

  return 0;
}

void dump( list< string > &name ) {
  list< string >::const_iterator it; // list iterator
  // print list to standard output
  it = name.begin();
  while ( it != name.end() ) {
    cout << *it << endl;
    it++; // kinda like pointers
  }
}
