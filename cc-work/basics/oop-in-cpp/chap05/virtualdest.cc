/*
 * virtualdest.cc
 *
 * a sample demonstrates how to use virtual destructor.
 */
#include <iostream>
using namespace std;

class Base {
public:
  Base() {
    cout << endl << "Base() firing" << endl;
    p = new char[ 5 ]; // allocate 5 bytes
  }
  virtual ~Base() {
    cout << "~Base() firing" << endl;
    delete [] p;
  }
private:
  char *p;
};

class Derive : public Base {
public:
  Derive() {
    cout << "Derive() firing" << endl;
    q = new char[ 5000 ]; 
  }
  virtual ~Derive() {
    cout << "~Derive() firing" << endl;
    delete [] q;
  }
private:
  char *q;
};

void f();

int main() {
  int i;
  for ( i = 0; i < 3; i++ ) {
    f();
  }
  return 0;
}

void f() {
  Base *ptr;
  ptr = new Derive();
  delete ptr;
}
