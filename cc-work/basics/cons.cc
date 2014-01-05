/*
 * cons.cc
 * constructor and destructor exercises.
 */
#include <iostream>
using namespace std;

class C {
private:
  string name;
public:
  C() {
    name = "anonymous";
    cout << name << " constructing. " << endl;
  }
  C( const string &n ) {
    name = n;
    cout << name << " constructing." << endl;
  }
  ~C() {
    cout << name << " destructing." << endl;
  }
};

int main() {
  C c0( "hortense" );
  C c1;
  C c2( "foo" );
  cout << endl;
  C *p = new C(); // default constructor.
  delete p;
  return 0;
}
