#include <iostream>
using namespace std;

#define PI 3.1415927

class Circle {
private:
  double radius;
public:
  void init( double r ) {
    radius = r;
  }
  double circum() {
    return 2 * PI * radius;
  }
  double area() {
    return PI * radius * radius;
  }
};

int main() {
  double radius;
  Circle one;
  cout << "input a radius" << endl;
  cin >> radius;
  one.init( radius );
  cout << "the circum and area are: " << endl;
  cout << one.circum() << " " << one.area() << endl;
  return 0;
}
