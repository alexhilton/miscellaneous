/*
 * tradeperson2.cc
 *
 * another demonstration about Polymophism mechinism supported by
 * c++.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class TradePerson {
public:
  void sayHi() {
    cout << "Just Hi, from class TradePerson" << endl;
  }
};

class Tinker : public TradePerson {
public:
  void sayHi() {
    cout << "Hi, I Tinker, from class Tinker" << endl;
  }
};

class Tailor : public TradePerson {
public:
  void sayHi() {
    cout << "Hi, I Tailor, from class Tailor" << endl;
  }
};

int main() {
  srand( time( 0 ) );
  TradePerson *ptr[ 10 ]; // array of pointers to base class
  unsigned which, i;

  // randomly create TradePersons, Tinkers and Tailors
  for ( i = 0; i < 10; i++ ) {
    which = 1 + rand() % 3;
    switch ( which ) {
    case 1:
      ptr[ i ] = new TradePerson;
      break;
    case 2:
      ptr[ i ] = new Tinker;
      break;
    case 3:
      ptr[ i ] = new Tailor;
      break;
    }
  }

  // polymophically invoke the sayHi methods
  for ( i = 0; i < 10; i++ ) {
    ptr[ i ]->sayHi();
    delete ptr[ i ];
  }

  return 0;
}
