/*
 * a Shape hierarchy.
 * base class shape is abstract class
 * five derived classes are Point, Line, Circle, Rectangle and Triangle.
 */
#include <iostream>
using namespace std;

class Shape {
public:
  virtual void draw() = 0;
  virtual void resize() = 0;
};

// Point
class Point : public Shape {
private:
  int x0, y0; // coordinate to be draw point
public:
  Point();
  Point( const int &x, const int &y );
  void setPoint( const int &x, const int &y );
  int getPointX() const;
  int getPointY() const;
  virtual void draw();
  virtual void resize();
};

Point::Point() {
  x0 = 0;
  y0 = 0;
}

Point::Point( const int &x, const int &y ) {
  x0 = x;
  y0 = y;
}

void Point::setPoint( const int &x, const int &y ) {
  x0 = x;
  y0 = y;
}

int Point::getPointX() const {
  return x0;
}

int Point::getPointY() const {
  return y0;
}

void Point::draw() {
  cout << "*" << endl;
}

void Point::resize() {
  cout << "resizing point..." << endl;
}

// Line
class Line : public Shape {
private:
  int x1, y1; // starting point
  int x2, y2; // ending point
public:
  Line();
  Line( const int &x0, const int &y0, const int &x, const int &y );
  void setStartPoint( const int &x0, const int &y0 );
  void setEndPoint( const int &x0, const int &y0 );
  virtual void draw();
  virtual void resize();
};

Line::Line() {
  x1 = 0;
  y1 = 0;
  x2 = 10;
  y2 = 10;
}

Line::Line( const int &x0, const int &y0, const int &x, const int &y ) {
  x1 = x0;
  y1 = y0;
  x2 = x;
  y2 = y;
}

void Line::setStartPoint( const int &x0, const int &y0 ) {
  x1 = x0;
  y1 = y0;
}

void Line::setEndPoint( const int &x0, const int &y0 ) {
  x1 = x0;
  y1 = y0;
}

void Line::draw() {
  int i;
  for ( i = 0; i < x2-x1; i++ ) {
    cout << "-";
  }
  cout << endl;
}

void Line::resize() {
  cout << "resizing line..." << endl;
}

// Circle
class Circle : public Shape {
private:
  int x0, y0; // center of circle
  int radius; // radius in pixel
public:
  Circle();
  Circle( const int &x, const int &y, const int &r );
  void setCenter( const int &x, const int &y );
  void setRadius( const int &r );
  virtual void draw();
  virtual void resize();
};

Circle::Circle() {
  x0 = 5;
  y0 = 5;
  radius = 3;
}

Circle::Circle( const int &x, const int &y, const int &r ) {
  x0 = x;
  y0 = y;
  radius = r;
}

void Circle::setCenter( const int &x, const int &y ) {
  x0 = x;
  y0 = y;
}

void Circle::setRadius( const int &r ) {
  radius = r;
}

void Circle::draw() {
  int i, j;

  cout << " ";
  for ( j = 0; j < radius; j++ ) {
    cout << "*";
  }
  cout << endl;

  for ( i = 0; i < radius-2; i++ ) {
    for ( j = 0; j < radius+2; j++ ) {
      cout << "*";
    }
    cout << endl;
  }

  cout << " ";
  for ( j = 0; j < radius; j++ ) {
    cout << "*";
  }
  cout << endl;
}

void Circle::resize() {
  cout << "resizing circle..." << endl;
}

// Triangle
class Triangle : public Shape {
private:
  int x1, y1; // up-top vertex
  int x2, y2; // left-lower vertex
  int x3, y3; // right-lower vertex
public:
  Triangle();
  Triangle( const int &xt1, const int &yt1, const int &xt2, 
		  const int &yt2, const int &xt3, const int &yt3 );
  void setTop( int &xt, int &yt );
  void setLeftDown( int &xt, int &yt );
  void setRightDown( int &xt, int &yt );
  virtual void draw();
  virtual void resize();
};

Triangle::Triangle() {
  x1 = 6;
  y1 = 0;
  x2 = 2;
  y2 = 4;
  x3 = 10;
  y3 = 4;
}

Triangle::Triangle( const int &xt1, const int &yt1, const int &xt2, 
		const int &yt2, const int &xt3, const int &yt3 ) {
  x1 = xt1;
  y1 = yt1;
  x2 = xt2;
  y2 = yt2;
  x3 = xt3;
  y3 = yt3;
}

void Triangle::setTop( int &xt1, int &yt1 ) {
  x1 = xt1;
  y1 = yt1;
}

void Triangle::setLeftDown( int &x, int &y ) {
  x2 = x;
  y2 = y;
}

void Triangle::setRightDown( int &x, int &y ) {
  x3 = x;
  y3 = y;
}

void Triangle::draw() {
  int i;
  int h = y2 - y1; // height of triangle in pixel
  int j;
  for ( i = 1; i <= h; i++ ) {
    for ( j = 0; j < h-i; j++ ) {
      cout << " ";
    }
    for ( j = 0; j < 2*i-1; j++ ) {
      cout << "*";
    }
    cout << endl;
  }
}

void Triangle::resize() {
  cout << "resizing triangle..." << endl;
}

// Rectangle
class Rectangle : public Shape {
private:
  int x1, y1; // upper-left
  int x2, y2; // upper-right
  int x3, y3; // lower-left
  int x4, y4; // lower-right
public:
  Rectangle();
  Rectangle( int xt1, int yt1, int xt2, int yt2, 
	     int xt3, int yt3, int xt4, int yt4 );
  void setUpperLeft( int xt1, int yt1 );
  void setUpperRight( int xt1, int yt1 );
  void setLowerLeft( int xt1, int yt1 );
  void setLowerRight( int xt1, int yt1 );
  virtual void draw();
  virtual void resize();
};

Rectangle::Rectangle() {
  x1 = 0;
  y1 = 0;
  x2 = 8;
  y2 = 0;
  x3 = 0;
  y3 = 4;
  x4 = 8;
  y4 = 4;
}

Rectangle::Rectangle( int xt1, int yt1, int xt2, int yt2, 
		      int xt3, int yt3, int xt4, int yt4 ) {
  x1 = xt1;
  y1 = yt1;
  x2 = xt2;
  y2 = yt2;
  x3 = xt3;
  y3 = yt3;
  x4 = xt4;
  y4 = yt4;
}

void Rectangle::setUpperLeft( int xt1, int yt1 ) {
  x1 = xt1;
  y1 = yt1;
}

void Rectangle::setUpperRight( int x, int y ) {
  x2 = x;
  y2 = y;
}

void Rectangle::setLowerLeft( int x, int y ) {
  x3 = x;
  y3 = y;
}

void Rectangle::setLowerRight( int x, int y ) {
  x4 = x;
  y4 = y;
}

void Rectangle::draw() {
  int i, j;
  int h = y3 - y1;
  int w = x2 - x1;
  for ( i = 0; i < h; i++ ) {
    for ( j = 0; j < w; j++ ) {
      cout << "*";
    }
    cout << endl;
  }
}

void Rectangle::resize() {
  cout << "resizing rectangle..." << endl;
}

void clear() {
  char ch;
  cout << "input 'n' to continue...";
  cin >> ch;
}

int main() {
  Point p1;
  Point p2( 3, 4 );
  p1.draw();
  p1.resize();
  p2.draw();
  p2.resize();
  clear();

  Line l1;
  Line l2( 1, 2, 6, 7 );
  l1.draw();
  l1.resize();
  l2.draw();
  l2.resize();
  clear();

  Circle c1;
  Circle c2( 4, 4, 5 );
  c1.draw();
  c1.resize();
  c2.draw();
  c2.resize();
  clear();

  Triangle t1;
  Triangle t2( 6, 0, 2, 6, 10, 6 );
  t1.draw();
  t1.resize();
  t2.draw();
  t2.resize();
  clear();

  Rectangle r1;
  Rectangle r2( 2, 0, 8, 0, 2, 4, 8, 4 );
  r1.draw();
  r1.resize();
  r2.draw();
  r2.resize();
  clear();

  return 0;
}
