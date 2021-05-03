// File: ListCSV/LCSVzipVis.hpp

#ifndef LCSVZIPVIS_HPP_
#define LCSVZIPVIS_HPP_

#include <iostream>
#include "ListCSV.hpp"
#include "AListCSVVis.hpp"
using namespace std;

// ========= LCSVzipVis =========
template<class T>
class LCSVzipVis : public AListCSVVis<T> {
private:
    ListCSV<T> &_other; // Input parameter, modified by visitor.

public:
    // ========= Constructor =========
    LCSVzipVis(ListCSV<T> &other):
        _other(other) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: This host list is a perfect shuffle of the host list and other,
    // starting with the first element of the host list.
    // other is the empty list (cut zip, as opposed to copy zip).
    void emptyCase(ListCSV<T> &host) override {
        cerr << "LCSVzipVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        cerr << "LCSVzipVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVzipVis precondition violated: Cannot zip const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVzipVis precondition violated: Cannot zip const list." << endl;
        throw -1;
    }
};

// Global function for convenience.
// Post: This host list is a perfect shuffle of list and other,
// starting with the first element of list.
// other is the empty list (cut zip, as opposed to copy zip).
template<class T>
void zip(ListCSV<T> &list, ListCSV<T> &other) {
    cerr << "zip: Exercise for the student." << endl;
    throw -1;
}

#endif
