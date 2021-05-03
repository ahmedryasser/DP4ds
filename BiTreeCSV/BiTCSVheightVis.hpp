// File: BiTreeCSV/BiTCSVheightVis.hpp

#ifndef BITCSVHEIGHTVIS_HPP_
#define BITCSVHEIGHTVIS_HPP_

#include <iostream>
#include "BiTreeCSV.hpp"
#include "ABiTreeCSVVis.hpp"
using namespace std;

// ========= BiTCSVheightVis =========
template<class T>
class BiTCSVheightVis : public ABiTreeCSVVis<T> {
private:
    int _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVheightVis() {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        _result=0;

    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        int numL = 1+ numLeaves(host.left());
        int numR = 1+ numLeaves(host.right());
        _result= numL > numR?numL:numR;
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _result=0;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        int numL = 1+ numLeaves(host.left());
        int numR = 1+ numLeaves(host.right());
        _result= numL > numR?numL:numR;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The height of the host tree is returned.
    int result() const {
        return _result;
    }
};

// Global function for convenience
template<class T>
int height(BiTreeCSV<T> const &tree) {
    BiTCSVheightVis<T> heightVis;
    tree.accept(heightVis);
    return heightVis.result();
}

#endif
