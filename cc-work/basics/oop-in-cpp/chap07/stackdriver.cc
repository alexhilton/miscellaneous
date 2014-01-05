#include "stack.hh"

int main() {
  const string prompt = "Enter an algebraic expressions: ";
  const char lparen = '(';
  const char rparen = ')';
  Stack< char > s;
  string buf;
  unsigned i;
  char tmp;

  // **** read fully parenthesized algebraic expressions
  // from standard input
  cout << prompt << endl;
  getline( cin, buf );
  // push characters in expression onto stack
  // trimming white spaces
  for ( i = 0; i < buf.length(); i++ ) {
    if ( !isspace( buf[ i ] ) ) {
      s.push( buf[ i ] );
    }
  }

  cout << "Original expression: " << buf << endl;
  cout << "Expression in reverse: ";

  // pop chracters from stack, exchanging left parenthesises
  // for right one and vice versa
  while ( !s.empty() ) {
    tmp = s.pop();
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
