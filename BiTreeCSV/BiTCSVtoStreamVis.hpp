// File: BiTreeCSV/BiTCSVtoStreamVis.hpp

#ifndef BITCSVTOSTREAMVIS_HPP_
#define BITCSVTOSTREAMVIS_HPP_

template<class T> class BiTCSVtoStreamHelperVis; // Forward reference.

#include <iostream>
#include "BiTreeCSV.hpp"
#include "ABiTreeCSVVis.hpp"
using namespace std;

// ========= BiTCSVtoStreamVis =========
template<class T>
class BiTCSVtoStreamVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    // ========= Constructor =========
    BiTCSVtoStreamVis(ostream &os):
        _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A string representation of this tree is sent to os.
    void emptyCase(BiTreeCSV<T> &host) override {
        _os << "*";
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisR
            ("     ", "     ", "    |", _os);
        host.right().accept(toStreamHelperVisR);
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisL
            ("    |", "     ", "     ", _os);
        host.left().accept(toStreamHelperVisL);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _os << "*";
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisR
            ("     ", "     ", "    |", _os);
        host.right().accept(toStreamHelperVisR);
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisL
            ("    |", "     ", "     ", _os);
        host.left().accept(toStreamHelperVisL);
    }
};

// ========= BiTCSVtoStreamHelperVis =========
template<class T>
class BiTCSVtoStreamHelperVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.
    string _prRight; // Input parameter.
    string _prRoot; // Input parameter.
    string _prLeft; // Input parameter.

public:
    // ========= Constructor =========
    BiTCSVtoStreamHelperVis(string prRight, string prRoot, string prLeft, ostream &os):
        _os(os),
        _prRight(prRight),
        _prRoot(prRoot),
        _prLeft(prLeft) {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        _os << _prRoot << "-*" << endl;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisR
            (_prRight + "     ", _prRight + "     ", _prRight + "    |", _os);
        host.right().accept(toStreamHelperVisR);
        _os << _prRoot;
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisL
            (_prLeft + "    |", _prLeft + "     ", _prLeft + "     ", _os);
        host.left().accept(toStreamHelperVisL);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _os << _prRoot << "-*" << endl;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisR
            (_prRight + "     ", _prRight + "     ", _prRight + "    |", _os);
        host.right().accept(toStreamHelperVisR);
        _os << _prRoot;
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSVtoStreamHelperVis<T> toStreamHelperVisL
            (_prLeft + "    |", _prLeft + "     ", _prLeft + "     ", _os);
        host.left().accept(toStreamHelperVisL);
    }
};

// ========= operator<< =========
template<class T>
ostream &operator<< (ostream &os, BiTreeCSV<T> const &tree) {
    BiTCSVtoStreamVis<T> toStreamVis(os);
    tree.accept(toStreamVis);
    return os;
}

#endif
