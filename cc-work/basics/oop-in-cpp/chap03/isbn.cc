/*
 * isbn.cc
 * implement a class for ISBN -- International Standard Book Number.
 * and provide a method to check whether a book is valid.
 */
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class ISBN {
private:
  string number;
  char lastDigit;
public:
  ISBN() {;}
  ISBN( string &n ) {
    number = n;
  }
  void setNumber( const string &n ) {
    number = n;
  }
  string getNumber() const {
    return number;
  }
  bool check() const {
    int mul = 1, i, sum = 0, len = number.length();
    for ( i = 0; i < len && mul <= 9; i++ ) {
      if ( isdigit( number[i] ) ) {
	sum += (number[i]-'0') * mul;
	mul++;
      }
    }
    sum %= 11;
    if ( sum == 10 ) {
      if ( number[ len-1 ] == 'X' ) {
	return true;
      } else {
	return false;
      }
    } else {
      if ( number[ len-1 ] == (sum+'0') ) {
	return true;
      } else {
	return false;
      }
    }
  }
};

int main() {
  ISBN one;
  string n;
  n = "0-670-82162-4";
  ISBN two( n );
  n = "7-302-11240-1";
  one.setNumber( n );
  cout << one.check() << endl;
  cout << two.check() << endl;
  return 0;
}
