#include <iostream>
using namespace std;

class Parent {
public:
    int parent;
    Parent() : parent(0) { }
    virtual void f() {
        cout << "Parent::f()" << endl;
    }
    
    virtual void g() {
        cout << "Parent::g()" << endl;
    }

    virtual void h() {
        cout << "Parent::h()" << endl;
    }
};

class Child : public Parent {
public:
    int child;
    Child() : child(100) {}
    virtual void f() {
        cout << "Child::f()" << endl;
    }

    virtual void g_child() {
        cout << "Child::g_child()" << endl;
    }

    virtual void h_child() {
        cout << "Child::h_child()" << endl;
    }

};

class GrandChild : public Child {
public:
    int grandChild;
    GrandChild() : grandChild(10000) {}
    virtual void f() {
        cout << "GrandChild::f()" << endl;
    }

    virtual void g_child() {
        cout << "GrandChild::g_child()" << endl;
    }

    virtual void h_grand_child() {
        cout << "GrandChild::h_grand_child()" << endl;
    }
};

typedef void (*func)();

int main() {
    GrandChild gc;
    int **pvtab = (int **) &gc;
    cout << "[0] grand child::_vptr->" << endl;
    for (int i = 0; (func) pvtab[0][i] != NULL; i++) {
        func pfunc = (func) pvtab[0][i];
        cout << "   [" << i << "]";
        pfunc();
    }

    cout << "[1] Parent.parent = " << (int) *pvtab[1] << endl;
    cout << "[2] Child.child = " << (int) *pvtab[2] << endl;
    cout << "[3] GrandChild.grandChild = " << (int) *pvtab[3] << endl;
    return 0;
}
