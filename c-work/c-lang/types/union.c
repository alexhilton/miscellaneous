/*
 * union.c
 * try out union.
 */
#include <stdio.h>

int main() {
  union {
    double d;
    float f;
  } var;
  var.d = 10.0;
  printf( "put in a double, pull out a float f = %f\n", var.f );

  var.f = 10.0;
  printf( "put in a float, pull out a double d = %lf\n", var.d );
  return 0;
}
