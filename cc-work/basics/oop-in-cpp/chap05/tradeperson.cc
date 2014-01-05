/*
 * tradeperson.cc
 *
 * demonstrate the Polymophism Mechinism, i.e. dynamic-binding tech
 */
#include <iostream>
using namespace std;

class TradePerson {
public:
  virtual void sayHi() {
    cout << "Just hi. from class TradePerson" << endl;
  }
};

class Tinker : public TradePerson {
public:
  virtual void sayHi() {
    cout << "Hi, I tinker. from class Tinker" << endl;
  }
};

class Tailor : public TradePerson {
public:
  virtual void sayHi() {
    cout << "Hi, I Tailor, from class Tailor" << endl;
  }
};

int main() {
  TradePerson *p; // pointer to base class, used to dynamic-binding
  int which;

  /* 
   * prompt  user for a number
   * *** 1 -- TradePerson
   *     2 -- Tinker
   *     3 -- Tailor
   */
  do {
    cout << "1 == TradePerson, 2 == Tinker, 3 == Tailor" << endl;
    cin >> which;
  } while ( which < 1 || which > 3 );
  // set pointer p depending on user choice
  switch ( which ) {
  case 1:
    p = new TradePerson; 
    break;
  case 2:
    p = new Tinker;
    break;
  case 3:
    p = new Tailor;
    break;
  }

  // invoke the sayHi method via the pointer
  p->sayHi(); // run-time binding in effect.
  delete p;
  return 0;
}
