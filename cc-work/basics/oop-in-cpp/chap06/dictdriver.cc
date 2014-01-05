#include <iostream>
#include "dict.hh"

int main() {
  Dict d;
  d[ "residual fm" ] = "incidental fm";
  d[ "pixel" ] = "in a daffy state";

  cout << endl << endl << "dump" << d;

  d[ "pixel" ] = "picture element";
  cout << endl << endl << "dump" << d;

  cout << endl << endl << "lookup" << endl;
  cout << d[ "residual fm" ];
  cout << d[ "pixel" ];
  cout << d[ "pixie" ] << endl;
  return 0;
}
