/*
 * check out accssibility of protected members.
 * private and protected members are visible in class,
 * not accessible by object.
 */
#include <iostream>
using namespace std;

class Example {
private:
  int a;
protected:
  int b;
public:
  int c;
};

int main() {
  Example three;
  printf( "c is %d\n", three.c );
  return 0;
}
