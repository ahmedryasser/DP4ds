// File: ArrayP/ArrayP.hpp

#ifndef ARRAYP_HPP_
#define ARRAYP_HPP_

#include <iostream> // istream, ostream.
#include "ASeq.hpp"
using namespace std;

// ========= ArrayP =========
// Pre: The parameter P is a pointer type.
template<class P>
class ArrayP : public ASeq<P> {
private:
    P *_data;
    int _cap;

public:
    ArrayP(int cap = 1);
    virtual ~ArrayP();
    int cap() const override;
    P &operator[](int i) override; // For read/write.
    P const &operator[](int i) const override; // For read-only.

private:
    ArrayP(ArrayP const &rhs); // Disabled.
    ArrayP &operator=(ArrayP const &rhs); // Disabled.
};

// ========= Constructor =========
template<class P>
ArrayP<P>::ArrayP(int cap) {
    if (cap < 1) {
        cerr << "ArrayP constructor precondition violated: cap cannot be less than 1." << endl;
        throw -1;
    }
    _data = new P[cap];
    _cap = cap;
    for (int i = 0; i < _cap; i++) {
        _data[i] = nullptr;
    }
}

// ========= Destructor =========
template<class P>
ArrayP<P>::~ArrayP() {
    for (int i = 0; i < _cap; i++) { // Differs for ArrayT.
        delete _data[i];
        _data[i] = nullptr;
    }
    delete [] _data;
    _data = nullptr;
}

// ========= cap =========
template<class P>
int ArrayP<P>::cap() const {
    return _cap;
}

// ========= operator[] =========
template<class P>
P &ArrayP<P>::operator[](int i) {
    if (i < 0 || _cap <= i) {
        cerr << "ArrayP index out of bounds: index == " << i << endl;
        throw -1;
    }
    return _data[i];
}

template<class P>
P const &ArrayP<P>::operator[](int i) const {
    if (i < 0 || _cap <= i) {
        cerr << "ArrayP index out of bounds: index == " << i << endl;
        throw -1;
    }
    return _data[i];
}

// ========= writeStream =========
template<class P>
void writeStream(ostream &os, ArrayP<P> const &a, int len) {
    // Pre: << is defined for P*, which is a number.
    // Post: num values are output from a to os, where
    // num == min(len, a.cap()).
    int cap = a.cap();
    for (int i = 0; i < len && i < cap; i++) {
        os.width(12);
        os << *a[i];
        if (i % 6 == 5) {
            os << endl;
        }
    }
    os << endl;
}

#endif
