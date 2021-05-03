// File: ArrayT/ArrayT.hpp

#ifndef ARRAYT_HPP_
#define ARRAYT_HPP_

#include <iostream> // istream, ostream.
#include "ASeq.hpp"
using namespace std;

// ========= ArrayT =========
// Pre: The parameter T is not a pointer type.
template<class T>
class ArrayT : public ASeq<T> {
private:
    T *_data;
    int _cap;

public:
    ArrayT(int cap = 1);
    virtual ~ArrayT();
    int cap() const override;
    T &operator[](int i) override; // For read/write.
    T const &operator[](int i) const override; // For read-only.

private:
    ArrayT(ArrayT const &rhs); // Disabled.
    ArrayT &operator=(ArrayT const &rhs); // Disabled.
};

// ========= Constructor =========
template<class T>
ArrayT<T>::ArrayT(int cap) {
    if (cap < 1) {
        cerr << "ArrayT constructor precondition 0 < cap violated." << endl;
        cerr << "cap == " << cap << endl;
        throw -1;
    }
    _data = new T[cap];
    _cap = cap;
}

// ========= Destructor =========
template<class T>
ArrayT<T>::~ArrayT() {
    delete [] _data; // Differs for ArrayP.
    _data = nullptr;
}

// ========= cap =========
template<class T>
int ArrayT<T>::cap() const {
    return _cap;
}

// ========= operator[] =========
template<class T>
T &ArrayT<T>::operator[](int i) {
    if (i < 0 || _cap <= i) {
        cerr << "ArrayT index out of bounds: index == " << i << endl;
        throw -1;
    }
    return _data[i];
}

template<class T>
T const &ArrayT<T>::operator[](int i) const {
    if (i < 0 || _cap <= i) {
        cerr << "ArrayT index out of bounds: index == " << i << endl;
        throw -1;
    }
    return _data[i];
}

// ========= readStream =========
template<class T>
void readStream(istream &is, ArrayT<T> &a, int &len) {
    // Pre: >> is defined for T.
    // Post: num values are input from is to a, where
    // num == min(number of elements in is, a.cap()).
    // len == num.
    len = 0;
    int cap = a.cap();
    for (int i = 0; i < cap && is >> a[i]; i++) {
        len++;
    }
}

// ========= writeStream =========
template<class T>
void writeStream(ostream &os, ArrayT<T> const &a, int len) {
    // Pre: << is defined for T, which is a number.
    // Post: num values are output from a to os, six items per line, where
    // num == min(len, a.cap()).
    int cap = a.cap();
    for (int i = 0; i < len && i < cap; i++) {
        os.width(12);
        os.precision(6);
        os.setf(ios::fixed | ios::showpoint);
        os << a[i];
        if (i % 6 == 5) {
            os << endl;
        }
    }
    os << endl;
}

#endif
