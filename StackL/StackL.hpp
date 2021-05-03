// File: StackL/StackL.hpp

#ifndef STACKL_HPP_
#define STACKL_HPP_

#include <iostream> // ostream.
#include "ListL.hpp"
using namespace std;

// ========= StackL =========
template<class T>
class StackL {
private:
    ListL<T>* _listL;

public:
    StackL();
    // This stack is initialized to be empty.

    ~StackL();
    // Post: This stack is deallocated.

    bool isEmpty() const ;
    // Post: true is returned if this stack is empty; otherwise, false is returned.

    T pop();
    // Pre: This stack is not empty.
    // Post: The top value in this stack is removed and returned.

    void push(T const &val);
    // Post: val is stored on top of this stack.

    T const &topOf() const;
    // Pre: This stack is not empty.
    // Post: The top value from this stack is returned.

    void toStream(ostream &os) const;
    // Post: All the items on this stack from top to bottom are written to os.
};

// ========= Constructor =========
template<class T>
StackL<T>::StackL() {
    _listL = new ListL<T>();
}

// ========= Destructor =========
template<class T>
StackL<T>::~StackL() {
    delete _listL;
}

// ========= isEmpty =========
template<class T>
bool StackL<T>::isEmpty() const {
    return _listL->isEmpty();
}

// ========= pop =========
template<class T>
T StackL<T>::pop() {
    if (_listL->isEmpty()) {
        cerr << "pop precondition violated: Cannot pop from an empty stack." << endl;
        throw -1;
    }
    return _listL->remFirst();
}

// ========= push =========
template<class T>
void StackL<T>::push(const T &val) {
    _listL->prepend(val);
}

// ========= topOf =========
template<class T>
T const &StackL<T>::topOf() const {
    if (_listL->isEmpty()) {
        cerr << "pop precondition violated: Cannot topOf from an empty stack." << endl;
        throw -1;
    }
    return _listL->first();
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, StackL<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void StackL<T>::toStream(ostream &os) const {
    _listL->toStream(os);
}

#endif
