// File: SortProbe/ArrProbe.hpp

#ifndef ARRPROBE_HPP
#define ARRPROBE_HPP

#include <cassert>
// #include <iostream<cmath> // For debugging.

#include "ASeq.hpp"
#include "ArrayT.hpp"
#include "Counter.hpp"

// ========= ArrProbe =========
template<class T>
class ArrProbe : public ASeq<T> {
private:
    ArrayT<T> *_arrayT; // Does not own _arrayT.
    Counter _probeCount;

public:
    ArrProbe(ArrayT<T> *arrayT);
    virtual ~ArrProbe();

    T &operator[](int i) override; // For read/write.
    T const &operator[](int i) const override; // For read-only.

    int cap() const override { return _arrayT->cap(); }

    void clearProbeCount() { _probeCount.clear(); }

    int getProbeCount() const { return _probeCount.getCount(); }

    void setCost(int cost) { _probeCount.setDelta(cost); }

private:
    ArrProbe(ArrProbe const &rhs); // Disabled.
    ArrProbe &operator=(ArrProbe const &rhs); // Disabled.
};

// ========= Constructor =========
template<class T>
ArrProbe<T>::ArrProbe(ArrayT<T>* arrayT) :
    _arrayT(arrayT),
    _probeCount(1) {
}

// ========= Destructor =========
template<class T>
ArrProbe<T>::~ArrProbe() {
    _arrayT = nullptr;
}

// ========= operator[] =========
template<class T>
T &ArrProbe<T>::operator[](int i) {
    _probeCount.update();
    return (*_arrayT)[i];
}

template<class T>
T const &ArrProbe<T>::operator[](int i) const {
    return (*_arrayT)[i];
}

#endif
