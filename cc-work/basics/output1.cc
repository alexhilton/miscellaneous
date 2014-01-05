/*
 * output1.cc
 * output manipulator exercises.
 */
#include <iostream>
using namespace std;

int main() {
  int i = 91;
  cout << "i = " << i << " (decimal)" << endl;
  cout << "i = " << oct << i << " (octal)" << endl;
  cout << "i = " << hex << i << " (hexadecimal)" << endl;
  cout << "i = " << i << " (hexadecimal)" << endl;
  /*
   * the output is:
   * i = 91 ..
   * i = 133 ..
   * i = 5b ( hexadecimal );
   * i = 5b ( hexadecimal );
   * because once the status of cout is changed by using a manipulator
   * (other than setw) the status remain in effect until changed again.
   */

  return 0;
}
