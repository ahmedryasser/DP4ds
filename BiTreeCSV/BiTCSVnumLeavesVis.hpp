// File: BiTreeCSV/BiTCSVnumLeavesVis.hpp

#ifndef BITCSVNUMLEAVESVIS_HPP_
#define BITCSVNUMLEAVESVIS_HPP_

#include <iostream>
#include "BiTreeCSV.hpp"
#include "ABiTreeCSVVis.hpp"
#include "BiTCSVisEmptyVis.hpp"
using namespace std;

// ========= BiTCSVnumLeavesVis =========
template<class T>
class BiTCSVnumLeavesVis : public ABiTreeCSVVis<T> {
private:
    int _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVnumLeavesVis():
        _result(0) {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {

    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
//        if (isEmpty(host.left()) && isEmpty(host.right())){
//            int numL = host.left().accept(*this);
//            int numR = host.right().accept(*this);
//            _result= 1+ numL+ numR;
//        }
//        _result =  host.left().accept(*this)+ host.right().accept(*this);
        if (isEmpty(host.left()) && isEmpty(host.right())){
            host.left().accept(*this);
            host.right().accept(*this);
            _result++;
        }
        host.left().accept(*this);
        host.right().accept(*this);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {


    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        if (isEmpty(host.left()) && isEmpty(host.right())){
            host.left().accept(*this);
            host.right().accept(*this);
            _result++;
        }
        host.left().accept(*this);
        host.right().accept(*this);
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The number of leaves of the host tree is returned.
    int result() const {
        return _result;
    }
};

// Global function for convenience
template<class T>
int numLeaves(BiTreeCSV<T> const &tree) {
    BiTCSVnumLeavesVis<T> numLeavesVis;
    tree.accept(numLeavesVis);
    return numLeavesVis.result();
}

#endif
