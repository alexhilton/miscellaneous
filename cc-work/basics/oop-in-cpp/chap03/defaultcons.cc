/*
 * defaultcons.cc
 *
 * study of default constructor.
 */
#include <iostream>
#include <string>
using namespace std;

class Example {
private:
  string name;
public:
  Example() {} // default constructor
  Example( const string &str ) {
    name = str;
  }
  void print() {
    cout << "name is '" << name << "'" << endl;
  }
};

int main() {
  Example two; // using default constructor
  Example three( "hitlion" ); // using argumented constructor
  three.print();
  return 0;
}
