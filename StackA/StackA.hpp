// File: StackA/StackA.hpp

#ifndef STACKA_HPP_
#define STACKA_HPP_

#include "ArrayT.hpp"

// ========= StackA =========
template<class T>
class StackA {
private:
    ArrayT<T> _data;
    int _top;

public:
    StackA(int cap);
    // Post: This stack is allocated with a capacity of cap
    // and initialized to be empty.

    bool isEmpty() const;
    // Post: true is returned if this stack is empty; otherwise, false is returned.

    bool isFull() const;
    // Post: true is returned if this stack is full; otherwise, false is returned.

    T pop();
    // Pre: This stack is not empty.
    // Post: The top value in this stack is removed and returned.

    void push(T const &val);
    // Pre: This stack is not full.
    // Post: val is stored on top of this stack.

    T const &topOf() const;
    // Pre: This stack is not empty.
    // Post: The top value from this stack is returned.

    void toStream(ostream &os) const;
    // Post: All the items on this stack from top to bottom are written to os.
};

// ========= Constructor =========
template<class T>
StackA<T>::StackA(int cap):
    _data(cap),
    _top(-1) {
}

// ========= isEmpty =========
template<class T>
bool StackA<T>::isEmpty() const {
    return _top == -1;
}

// ========= isFull =========
template<class T>
bool StackA<T>::isFull() const {
    return _top == _data.cap()-1;
}

// ========= pop =========
template<class T>
T StackA<T>::pop() {
    if (isEmpty()) {
        cerr << "pop precondition violated: Cannot pop from an empty stack." << endl;
        throw -1;
    }
    T temp = _data[_top];
    _top--;
    return temp;
}

// ========= push =========
template<class T>
void StackA<T>::push(T const &val) {
    _top++;
    _data[_top] = val;
}

// ========= topOf =========
template<class T>
T const &StackA<T>::topOf() const {
    if (isEmpty()) {
        cerr << "topOf precondition violated: An empty stack has no top." << endl;
        throw -1;
    }
    return _data[_top];
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, StackA<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void StackA<T>::toStream(ostream &os) const {
    os << "(";
    for (int i = _top; i > 0; i--) {
        os << _data[i] << ", ";
    }
    if (_top == -1) {
        os << ")";
    }
    else {
        os << _data[0] << ")";
    }
}

#endif
