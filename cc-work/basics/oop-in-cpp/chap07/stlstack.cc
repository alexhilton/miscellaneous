/*
 * stlstack.cc
 *
 * STL stack at a first glance
 */
#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

int main() {
  const string prompt = "enter an algebraic expression";
  const char lparen = '(';
  const char rparen = ')';
  stack< char > s;
  string buf;
  int i;

  /* 
   * *** read fully parenthesized algebraic expression
   * from standard input.
   */
  cout << prompt << endl;
  getline( cin, buf );

  /*
   * push chracters in expression onto stack trimming white spaces
   */
  for ( i = 0; i < (int) buf.length(); i++ ) {
    if ( !isspace( buf[ i ] ) ) {
      s.push( buf[ i ] );
    }
  }

  cout << "Original expression: " << buf << endl;
  cout << "Expression in reverse:" << endl;
  /*
   * pop characters from stack, exchanging left parenthesises
   * for right parenthesises and vice-versa
   */
  while ( !s.empty() ) {
    char tmp = s.top(); // get top element
    s.pop(); // remove it
    if ( tmp == lparen ) {
      tmp = rparen;
    } else if ( tmp == rparen ) {
      tmp = lparen;
    }
    cout << tmp;
  }
  cout << endl;

  return 0;
}
