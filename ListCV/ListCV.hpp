// File: ListCV/ListCV.hpp

#ifndef LISTCV_HPP_
#define LISTCV_HPP_

#include <iostream> // ostream.
#include <cassert>
#include "AListCV.hpp"
#include "AListCVVis.hpp"
#include "LCVcloneVis.hpp"

using namespace std;

// ========= The empty (MT) list =========
template<class T>
class MTListCV : public AListCV<T> {

public:
    MTListCV() { }
    void accept(AListCVVis<T> &visitor) const;

private:
    MTListCV(MTListCV<T> const &rhs); // Disabled.
    MTListCV &operator=(MTListCV<T> const &rhs); // Disabled.
};

// ========= The non-empty(NE) list =========
template<class T>
class NEListCV : public AListCV<T> {
private:
    T _first;
    AListCV<T> *_rest;

private:
    NEListCV(NEListCV<T> const &rhs); // Disabled.
    NEListCV &operator=(NEListCV<T> const &rhs); // Disabled.

public:
    NEListCV(T first);
    // Post: This list exists and contains exactly one element, first.

    NEListCV(T first, AListCV<T> const *rest);
    // Post: This list exists and contains first and a copy of rest.

    ~NEListCV();
    // Pre: This list exists.
    // Post: All internal members are deallocated.

    T const first() const;
    AListCV<T> const *rest() const;

    void accept(AListCVVis<T> &visitor) const;
};

// ========= Constructors =========
template<class T>
NEListCV<T>::NEListCV(T first): _first(first), _rest(new MTListCV<T>()) {
}

template<class T>
NEListCV<T>::NEListCV(T first, AListCV<T> const *rest): _first (first) {
    LCVcloneVis<T> cloneVis;
    rest->accept(cloneVis);
    _rest = cloneVis.result();
}

// ========= Destructor =========
template<class T>
NEListCV<T>::~NEListCV() {
    delete _rest;
}

// ========= first and rest =========
template<class T>
T const NEListCV<T>::first() const {
    return _first;
}

template<class T>
AListCV<T> const *NEListCV<T>::rest() const {
    return _rest;
}

// ========= accept =========
template<class T>
void MTListCV<T>::accept(AListCVVis<T> &visitor) const {
    visitor.visitMTList(*this);
}

template<class T>
void NEListCV<T>::accept(AListCVVis<T> &visitor) const {
    visitor.visitNEList(*this);
}

#endif
