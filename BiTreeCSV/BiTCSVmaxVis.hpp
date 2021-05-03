// File: BiTreeCSV/BiTCSVmaxVis.hpp

#ifndef BITCSVMAXVIS_HPP_
#define BITCSVMAXVIS_HPP_

#include <iostream>
#include "BiTreeCSV.hpp"
#include "ABiTreeCSVVis.hpp"
using namespace std;

// ========= BiTCSVmaxVis =========
template<class T>
class BiTCSVmaxVis : public ABiTreeCSVVis<T> {
private:
    T const *_result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVmaxVis() {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        cerr << "BiTCSVmaxVis precondition violated: "
             << "An empty tree has no maximum." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        T const *dataTemp = &host.root(); // To avoid restrictions on T const &_data.
        T const *leftMax = (isEmpty(host.left())) ?
            dataTemp : (host.left().accept(*this), &result());
        T const *rightMax = (isEmpty(host.right())) ?
            dataTemp : (host.right().accept(*this), &result());
        _result = &((*leftMax > *rightMax) ?
                    ((*leftMax > *dataTemp) ? *leftMax : *dataTemp) :
                    ((*rightMax > *dataTemp) ? *rightMax : *dataTemp));
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVmaxVis precondition violated: "
             << "An empty tree has no maximum." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        T const *dataTemp = &host.root(); // To avoid restrictions on T const &_data.
        T const *leftMax = (isEmpty(host.left())) ?
            dataTemp : (host.left().accept(*this), &result());
        T const *rightMax = (isEmpty(host.right())) ?
            dataTemp : (host.right().accept(*this), &result());
        _result = &((*leftMax > *rightMax) ?
                    ((*leftMax > *dataTemp) ? *leftMax : *dataTemp) :
                    ((*rightMax > *dataTemp) ? *rightMax : *dataTemp));
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The maximum element of the host tree is returned.
    T const &result() const {
        return *_result;
    }
};

// Global function for convenience
template<class T>
T const &max(BiTreeCSV<T> const &tree) {
    BiTCSVmaxVis<T> maxVis;
    tree.accept(maxVis);
    return maxVis.result();
}

#endif
