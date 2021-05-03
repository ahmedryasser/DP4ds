// File: ListCSV/LCSVequalsVis.hpp

#ifndef LCSVEQUALSVIS_HPP_
#define LCSVEQUALSVIS_HPP_

#include <iostream>
#include "ListCSV.hpp"
#include "AListCSVVis.hpp"
#include "LCSVisEmptyVis.hpp"
using namespace std;

template<class T> class LCSVequalsHelperVis; // Forward declaration.

// ========= LCSVequalsVis =========
template<class T>
class LCSVequalsVis : public AListCSVVis<T> {
private:
    ListCSV<T> const &_rhs; // Input parameter.
    bool _result; // Output result.

public:
    // ========= Constructor =========
    LCSVequalsVis(ListCSV<T> const &rhs):
        _rhs(rhs) {
    }

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        LCSVisEmptyVis<T> isEmptyVis;
        host.accept(isEmptyVis);
        _result = isEmptyVis.result();
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        LCSVequalsHelperVis<T> equalsHelperVis(host.first(), host.rest());
        _rhs.accept(equalsHelperVis);
        _result = equalsHelperVis.result();
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        LCSVisEmptyVis<T> isEmptyVis;
        host.accept(isEmptyVis);
        _result = isEmptyVis.result();
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        LCSVequalsHelperVis<T> equalsHelperVis(host.first(), host.rest());
        _rhs.accept(equalsHelperVis);
        _result = equalsHelperVis.result();
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if the host list is equal to rhs; otherwise, false is returned.
    // Two lists are equal if they contain the same number of equal elements in the same order.
    bool result() const {
        return _result;
    }
};

// ========= LCSVequalsHelperVis =========
template<class T>
class LCSVequalsHelperVis : public AListCSVVis<T> {
private:
    T const &_first; // Input parameter.
    ListCSV<T> const &_rest; // Input parameter.
    bool _result; // Output result.

public:
    // ========= Constructor =========
    LCSVequalsHelperVis(T const &first, ListCSV<T> const &rest):
        _first(first),
        _rest(rest) {
    }

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        _result = false;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        LCSVequalsVis<T> equalsVis(host.rest());
        host.accept(equalsVis);
//        _result =  host.first() == _first && _rest.result(equalsVis);
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        _result = false;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        LCSVequalsVis<T> equalsVis(host.rest());
        host.accept(equalsVis);
//        _result =  host.first() == _first && _rest.result(equalsVis);
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if first equals host.first() and rest equals host.rest();
    // otherwise, false is returned.
    bool result() const {
        return _result;
    }
};

// Global function for convenience.
// ========= operator== =========
template<class T>
bool operator==(ListCSV<T> const &lhs, ListCSV<T> const &rhs) {
    LCSVequalsVis<T> equalsVis(rhs);
    rhs.accept(equalsVis);
    return equalsVis.result();
}

#endif
