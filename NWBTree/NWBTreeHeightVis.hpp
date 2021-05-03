// File: NWBTree/NWBTreeHeightVis.hpp

#ifndef NWBTREEHEIGHTVIS_HPP_
#define NWBTREEHEIGHTVIS_HPP_

#include <iostream>
#include "ANTreeVis.hpp"
using namespace std;

// ========= NWBTreeHeightVis =========
template<class T>
class NWBTreeHeightVis : public ANTreeVis<T> {
private:
    int _result; // Output result.

public:
    // ========= Constructor =========
    NWBTreeHeightVis() :
        _result(0) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            _result = 0;
            break;

        }
        default:
        {
            NWBTreeHeightVis<T> TreeHeightVis;
            host.getChild(0)->accept(TreeHeightVis);
            _result = 1+ TreeHeightVis.result();        }
            break;

        }
    }

    // ========= visit const =========
    void caseAt(int size, NTree<T> const &host) override {
        switch (size) {
        case 0:
        {
            _result = 0;
            break;
        }
        default:
        {
            NWBTreeHeightVis<T> TreeHeightVis;
            host.getChild(0)->accept(TreeHeightVis);
            _result = 1+ TreeHeightVis.result();
            break;
        }
        }
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The height of the tree is returned.

    int result() const {
        return _result;
    }
};

// Global function for convenience

template<class T>
int height(NTree<T> const &tree) {
    NWBTreeHeightVis<T> heightVis;
    tree.accept(heightVis);
    return heightVis.result();
}

#endif
