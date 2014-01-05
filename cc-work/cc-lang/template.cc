#include <iostream>

using namespace std;

template <class T>
class Stack {
public:
    Stack(int c);
    ~Stack();
    void push(T item);
    T pop();
    bool empty();
    bool full();
private:
    T *data;
    int current;
    int capacity;
};

template <class T>
Stack<T>::Stack(int c) : current(0) {
    if (c <= 0) {
        capacity = 0;
        data = NULL;
        return;
    }
    data = new T[c];
    capacity = c;
}

template <class T>
Stack<T>::~Stack() {
    if (data != NULL) {
        delete data;
    }
}

template <class T>
void Stack<T>::push(T item) {
    if (full()) {
        return;
    }
    data[current++] = item;
}

template <class T>
T Stack<T>::pop() {
    if (empty()) {
        return (T) 0;
    }
    return data[--current];
}

template <class T>
bool Stack<T>::empty() {
    return current <= 0;
}

template <class T>
bool Stack<T>::full() {
    return current >= capacity;
}

template <class T>
T min(T *a, size_t len) {
    T t = a[0];
    for (int i = 1; i < len; i++) {
        if (t > a[i]) {
            t = a[i];
        }
    }
    return t;
}

int main(void) {
    cout << "function template" << endl;
    int a[] = {1, 2, 3, 4, 5};
    cout << min(a, 5) << endl;
    float d[] = {1.f, 2.f, 3.f, 4.f, 5.f};
    cout << min(d, 5) << endl;

    cout << "class template, a stack" << endl;
    Stack<int> ints(5);
    ints.push(1);
    ints.push(2);
    ints.push(3);
    cout << ints.pop() << endl;
    cout << ints.pop() << endl;
    cout << ints.pop() << endl;
    Stack<float> ds(4);
    ds.push(1.0f);
    ds.push(2.0f);
    ds.push(3.0f);
    cout << ds.pop() << endl;
    cout << ds.pop() << endl;
    cout << ds.pop() << endl;
    return 0;
}
