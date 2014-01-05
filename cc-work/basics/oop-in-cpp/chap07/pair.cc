/*
 * pair.cc
 *
 * implement a template pair class
 */
#include <iostream>
#include <string>
using namespace std;

template< class T1, class T2 >
class Pair {
private:
  T1 first;
  T2 second;
public:
  Pair() {
    first = 0;
    second = 1;
  }
  Pair( T1 f, T2 s ) {
    first = f;
    second = s;
  }
  void setFirst( T1 f ) {
    first = f;
  }
  void setSecond( T2 s ) {
    second = s;
  }
  T1 getFirst() const {
    return first;
  } 
  T2 getSecond() const {
    return second;
  }
  void swapping() {
    first -= second;
    second += first;
    first = ( second - first );
  }
  void output() const {
    cout << "first is: " << first << "\tsecond is: " << second << endl;
  }
};

int main() {
  Pair< int, int > one( 3, 4 );
  cout << "**** for integers... ****" << endl;
  cout << "before swapping..." << endl;
  one.output();
  one.swapping();
  one.output();
  Pair< double, double > two( 3.0, 4.0 );
  cout << "**** for doubles... ****" << endl;
  cout << "before swapping..." << endl;
  two.output();
  two.swapping();
  two.output();
  Pair< float, float > three( 3.0, 4.0 );
  cout << "**** for floats... ****" << endl;
  cout << "before swapping..." << endl;
  three.output();
  three.swapping();
  three.output();
  return 0;
}
  
