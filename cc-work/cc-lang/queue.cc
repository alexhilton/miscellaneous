/*
 * implement a queue with two stack.
 */
#include <iostream>
using namespace std;

class Stack {
public:
    void push(int n);
    int pop();
    bool empty();
    Stack();
    void print();
    ~Stack();
private:
    int data[10];
    int current;
};

Stack::Stack() {
    current = 0;
}

Stack::~Stack() {
    current = 0;
}

void Stack::push(int n) {
    data[current++] = n;
}

int Stack::pop() {
    if (empty()) {
        return -1;
    }
    return data[--current];
}

bool Stack::empty() {
    return current <= 0;
}

void Stack::print() {
    for (int i = 0; i < current; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

class Queue {
public:
    void enqueue(int n);
    int dequeue();
    Queue();
    ~Queue();
private:
    Stack front;
    Stack end;
};

Queue::Queue() : front(), end() {
}

Queue::~Queue() {
}

void Queue::enqueue(int n) {
    while (!front.empty()) {
        end.push(front.pop());
    }
    end.push(n);
    while (!end.empty()) {
        front.push(end.pop());
    }
}

int Queue::dequeue() {
    return front.pop();
}

int main(void) {
    Stack a;
    a.push(1);
    a.push(2);
    a.push(3);
    cout << "with stack:" << endl;
    cout << a.pop() << endl;
    cout << a.pop() << endl;
    cout << a.pop() << endl;
    cout << "now with queue:" << endl;
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    return 0;
}
