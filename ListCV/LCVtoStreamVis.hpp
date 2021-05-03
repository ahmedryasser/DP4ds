// File: ListCV/LCVtoStreamVis.hpp

#ifndef LCVtoStreamVis_hpp
#define LCVtoStreamVis_hpp

#include <iostream>
#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

// ========= LCVtoStreamHelperVis =========
template<class T>
class LCVtoStreamHelperVis : public AListCVVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    LCVtoStreamHelperVis(ostream &os);
    void visitMTList(MTListCV<T> const &host) override;
    void visitNEList(NEListCV<T> const &host) override;
};

// ========= Constructor =========
template<class T>
LCVtoStreamHelperVis<T>::LCVtoStreamHelperVis(ostream &os):
    _os(os) {
}

// ========= visit =========
template<class T>
void LCVtoStreamHelperVis<T>::visitMTList(MTListCV<T> const &) {
    _os << ")";
}

template<class T>
void LCVtoStreamHelperVis<T>::visitNEList(NEListCV<T> const &host) {
    _os << ", " << host.first();
    host.rest()->accept(*this);
}

// ========= LCVtoStreamVis =========
template<class T>
class LCVtoStreamVis : public AListCVVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    LCVtoStreamVis(ostream &os);
    void visitMTList(MTListCV<T> const &host) override;
    void visitNEList(NEListCV<T> const &host) override;
};

// ========= Constructor =========
template<class T>
LCVtoStreamVis<T>::LCVtoStreamVis(ostream &os):
    _os(os) {
}

// ========= visit =========
template<class T>
void LCVtoStreamVis<T>::visitMTList(MTListCV<T> const &) {
    _os << "()";
}

template<class T>
void LCVtoStreamVis<T>::visitNEList(NEListCV<T> const &host) {
    _os << "(" << host.first();
    LCVtoStreamHelperVis<T> toStreamHVis(_os);
    host.rest()->accept(toStreamHVis);
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, const AListCV<T> *rhs) {
    static LCVtoStreamVis<T> toStreamVis(os); // static for efficiency.
    rhs->accept(toStreamVis);
    return os;
}

#endif
