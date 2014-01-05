/*
 * newdel1.cc
 * more exercises about new and delete.
 */
#include <iostream>
using namespace std;

typedef struct P {
  int x;
  int y;
} *Point;

int main() {
  Point *a = new Point[ 2 ];
  a[ 0 ] = new P; // new is convinient but not as powerful as malloc
  a[ 1 ] = new P;
  cout << "input the first point: ";
  cin >> a[0]->x;
  cin >> a[0]->y;
  cout << "input the second point: ";
  cin >> a[1]->x;
  cin >> a[1]->x;
  double cosa;
  cosa = ( a[0]->x * a[1]->x + a[0]->y * a[1]->y );
  cosa /= sqrt( (double)a[1]->x * a[1]->x + (double)a[1]->y * a[1]->y );
  cosa /= sqrt( (double)a[0]->x * a[0]->x + (double)a[0]->y * a[0]->y );
  cout << "the cosine of its angle is: " << cosa << endl;
  delete a[0];
  delete a[1];
  delete []a;
  return 0;
}
