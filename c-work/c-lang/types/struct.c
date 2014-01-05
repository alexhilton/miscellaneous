/*
 * struct.c
 * a program to demonstrate tricks about structure.
 * hence union has the same properties as struct, so we 
 * do not discuss union individually. You can apply
 * all the tricks of struct to union.
 */
#include <stdio.h>

struct Point1 {
  int x;
  int y;
};
struct Point2 {
  int x;
  int y;
} a;

int main( void ) {
  struct Point1 c;
  c.x = 1;
  c.y = 3;
  a.x = 2;
  a.y = 4;

  return 0;
}
