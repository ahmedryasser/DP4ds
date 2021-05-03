// File: QueueL/QueueL.hpp

#ifndef QUEUEL_HPP_
#define QUEUEL_HPP_

#include <iostream> // ostream.
#include "ListL.hpp"
using namespace std;

// ========= QueueL =========
template<class T>
class QueueL {
private:
    ListL<T>* _listL;

public:
    QueueL();
    // This queue is allocated and initialized to be empty.

    ~QueueL();
    // Post: This queue is deallocated.

    T dequeue();
    // Pre: This queue is not empty.
    // Post: The head value in this queue is removed and returned.

    void enqueue(T const &val);
    // Post: val is stored at the tail of this queue.

    T const &headOf() const;
    // Pre: This queue is not empty.
    // Post: The head value from this queue is returned.

    bool isEmpty() const;
    // Post: true is returned if this queue is empty; otherwise, false is returned.

    void toStream(ostream &os) const;
    // Post: All the items on this queue from tail to head are written to os.
};

// ========= Constructor =========
template<class T>
QueueL<T>::QueueL() {
    _listL = new ListL<T>();
}

// ========= Destructor =========
template<class T>
QueueL<T>::~QueueL() {
    delete _listL;
}

// ========= dequeue =========
template<class T>
T QueueL<T>::dequeue() {
    return _listL->remFirst();
}

// ========= enqueue =========
template<class T>
void QueueL<T>::enqueue(T const &val) {
    _listL->append(val);
}

// ========= headOf =========
template<class T>
T const &QueueL<T>::headOf() const {
//    if (_listL->isEmpty()) {
//        cerr << "pop precondition violated: Cannot topOf from an empty stack." << endl;
//        throw -1;
//    }
    return _listL->first();
}

// ========= isEmpty =========
template<class T>
bool QueueL<T>::isEmpty() const {
    return _listL->isEmpty();
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, QueueL<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void QueueL<T>::toStream(ostream &os) const {
    _listL->toStream(os);
}

#endif
