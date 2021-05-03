// File: NWBTree/NWBTreeIsEmptyVis.hpp

#ifndef NWBTREEISEMPTYVIS_HPP_
#define NWBTREEISEMPTYVIS_HPP_

#include <iostream>
#include "ANTreeVis.hpp"
using namespace std;

// ========= NWBTreeIsEmptyVis =========
template<class T>
class NWBTreeIsEmptyVis : public ANTreeVis<T> {
private:
    bool _result; // Output result.

public:
    // ========= Constructor =========
    NWBTreeIsEmptyVis() {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            _result = true;
            break;
        }
        default:
        {
            _result = false;
            break;
        }
        }
    }

    // ========= visit const =========
    void caseAt(int size, NTree<T> const &host) override {
        switch (size) {
        case 0:
        {
            _result = true;
            break;
        }
        default:
        {
            _result = false;
            break;
        }
        }
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: true is returned if the host tree is empty;
    // otherwise, false is returned.

    bool result() const {
        return _result;
    }
};

// Global function for convenience

template<class T>
bool isEmpty(NTree<T> const &tree) {
    NWBTreeIsEmptyVis<T> isEmptyVis;
    tree.accept(isEmptyVis);
    return isEmptyVis.result();
}

#endif
