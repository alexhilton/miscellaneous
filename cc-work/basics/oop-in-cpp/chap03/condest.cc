/*
 * condest.cc
 *
 * constructor and destructor of a class.
 */
#include <iostream>
#include <string>
using namespace std;

class Example {
private:
  string name;
public:
  Example() {
    name = "anonymous";
    cout << name << " constructing" << endl;
  }
  Example( const char *n ) {
    name = n;
    cout << name << " constructing" << endl;
  }
  ~Example() {
    cout << name << " destructing" << endl;
  }
};

int main() {
  Example example1( "bortname" );
  Example example2;
  Example example3( "foo" );
  cout << endl;
  Example *ptr = new Example();
  delete ptr;
  ptr = new Example( "hitlion" );
  delete ptr;

  return 0;
}
