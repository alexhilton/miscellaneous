#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw();
};

class Triangle : public Shape {
public:
    void draw();
};

class Rectangle : public Shape {
public:
    void draw();
};

void Shape::draw() {
    cout << "drawing from shape" << endl;
}

void Triangle::draw() {
    cout << "drawing a triangular" << endl;
}

void Rectangle::draw() {
    cout << "drawing a rectangle " << endl;
}

int main(void) {
    Shape *a[3];
    a[0] = new Shape;
    a[1] = new Triangle;
    a[2] = new Rectangle;
    a[0]->draw();
    a[1]->draw();
    a[2]->draw();

    return 0;
}
