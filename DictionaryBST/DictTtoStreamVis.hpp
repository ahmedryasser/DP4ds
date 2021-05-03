// File: DictionaryBST/DictTtoStreamVis.hpp

#ifndef DICTTTOSTREAMVIS_HPP_
#define DICTTTOSTREAMVIS_HPP_

#include <iostream>
#include "ADictionary.hpp"
#include "ABiTreeCSVVis.hpp"
#include "BiTreeCSV.hpp"
using namespace std;

// ========= DictTtoStreamHelperVis =========
template<class T>
class DictTtoStreamHelperVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.
    string _prefix; // Input parameter.

public:
    // ========= Constructor =========
    DictTtoStreamHelperVis(ostream &os):
        _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A string representation of this tree is returned, prefixed with "|_" for the root,
    // prefix + "|  " for the left subtree, and prefix + "   " for the right subtree.
    void emptyCase(BiTreeCSV<T> &host) override {
        _os << "|_ ()";
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        _os << "|_ " << host.root() << endl;
        string pfx = _prefix;
        _os << pfx;
        _prefix = pfx + "|  ";
        host.left().accept(*this);
        _os << endl;
        _os << pfx;
        _prefix = pfx + "   ";
        host.right().accept(*this);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _os << "|_ ()";
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        _os << "|_ " << host.root() << endl;
        string pfx = _prefix;
        _os << pfx;
        _prefix = pfx + "|  ";
        host.left().accept(*this);
        _os << endl;
        _os << pfx;
        _prefix = pfx + "   ";
        host.right().accept(*this);
    }

    // ========= setPrefix =========
    void setPrefix(string const &prefix) {
        _prefix = prefix;
    }
};


// ========= DictTtoStreamVis =========
template<class T>
class DictTtoStreamVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    // ========= Constructor =========
    DictTtoStreamVis(ostream &os):
        _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A string representation of this tree is returned.
    void emptyCase(BiTreeCSV<T> &host) override {
        _os << "()";
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        _os << host.root() << endl;
        DictTtoStreamHelperVis<T> toStreamHVis(_os);
        toStreamHVis.setPrefix("|  ");
        host.left().accept(toStreamHVis);
        _os << endl;
        toStreamHVis.setPrefix("   ");
        host.right().accept(toStreamHVis);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _os << "()";
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        _os << host.root() << endl;
        DictTtoStreamHelperVis<T> toStreamHVis(_os);
        toStreamHVis.setPrefix("|  ");
        host.left().accept(toStreamHVis);
        _os << endl;
        toStreamHVis.setPrefix("   ");
        host.right().accept(toStreamHVis);
    }
};

#endif
