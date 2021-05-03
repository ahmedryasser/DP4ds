// File: NWBTree/NWBTreeNumNodesVis.hpp

#ifndef NWBTREENUMNODESVIS_HPP_
#define NWBTREENUMNODESVIS_HPP_

#include <iostream>
#include "ANTreeVis.hpp"
using namespace std;

// ========= NWBTreeNumNodesVis =========
template<class T>
class NWBTreeNumNodesVis : public ANTreeVis<T> {
private:
    int _result; // Output result.

public:
    // ========= Constructor =========
    NWBTreeNumNodesVis() :
        _result(0) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            _result++;
            for (int i = 0; i<= size; i++){
                host.getChild(i)->accept(*this);
            }
            break;
        }
        default:
        {
            for(int j =0; j< size-1; j++) {
                NWBTreeNumNodesVis<T> numNodesVis;
                host.getChild(j)->accept(numNodesVis);
                _result = 1+ numNodesVis.result();
            }
            break;
        }
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        switch (size) {
        case 0:
        {
            _result++;
            for (int i = 0; i<= size; i++){
                host.getChild(i)->accept(*this);
            }
            break;
        }
        default:
        {
            for(int j =0; j< size-1; j++) {
                NWBTreeNumNodesVis<T> numNodesVis;
                host.getChild(j)->accept(numNodesVis);
                _result = 1+ numNodesVis.result();
            }
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
int numNodes(NTree<T> const &tree) {
    NWBTreeNumNodesVis<T> numNodesVis;
    tree.accept(numNodesVis);
    return numNodesVis.result();
}

#endif
