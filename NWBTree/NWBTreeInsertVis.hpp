// File: NWBTree/NWBTreeInsertVis.hpp

#ifndef NWBTREEINSERTVIS_HPP_
#define NWBTREEINSERTVIS_HPP_

#include <functional>
#include "ANTreeVis.hpp"
#include "SplitUpAndApplyVis.hpp"
using namespace std;

template<class T> class NWBTreeInsertHelpVis; // Forward declaration.

// ========= NWBTreeInsertVis =========
template<class T>
class NWBTreeInsertVis : public ANTreeVis<T> {
private:
    int _order; // Input parameter.
    T _key; // Input parameter.

public:
    // ========= Constructor =========
    NWBTreeInsertVis(int order, int key) :
        _order(order), _key(key) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            NTree<T>* temp = new NTree<T> (_key);
            host.spliceAt(0, temp);
            delete temp;
            return;
        }
        default:
        {
            NWBTreeInsertHelpVis<T> ihv(_key, _order, [](NTree<T>&) {
                }); // C++11 no-op lambda function.
            host.accept(ihv);
        }
        }
    }

    // ========= visit const =========
    void caseAt(int, NTree<T> const &) override {
        cerr << "Cannot insert into a const NTree." << endl;
        throw -1;
    }
};

// ========= NWBTreeInsertHelperVis =========
template<class T>
class NWBTreeInsertHelpVis : public ANTreeVis<T> {
private:
    T _key; // Input parameter.
    function<void(NTree<T>&) > _cmd; // Input parameter, C++11 function variable.
    SplitUpAndApplyVis<T> _splitUpAndApply;

public:
    // ========= Constructor =========

    // Initialize _key to key.
    // Initialize _cmd to cmd.
    // Initialize _splitUpAndApply visitor attribute with order and cmd.
    NWBTreeInsertHelpVis(T key, int order, function<void(NTree<T>&) > cmd) :
        _key(key), _cmd(cmd), _splitUpAndApply(order, cmd) {
    }

    ~NWBTreeInsertHelpVis() {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            NTree<T> temp(_key); // Tree with one element.
            _cmd(temp); // Splice temp back to the parent tree.
            return;
        }
        default:
        {
            // Find the index of the child tree to insert the key.
            int k = 0;
            while (k < size && host.getData(k) < _key) {
                k++;
            }
            if (k < size && host.getData(k) == _key) {
                return; // Duplicate keys not allowed.
            }
            function<void(NTree<T>&) > oldCmd = _cmd;
            _cmd = [&host, k](NTree<T>& tree) { // Using C++11 closure.
                // Need to hold on to the child tree at index k
                // and delete it later to avoid memory leak.
                // See comment for NTree<T>::spliceAt.
                NTree<T>* child = host.getChild(k);
                host.spliceAt(k, &tree);
                delete child;
            };
            _splitUpAndApply.setCmd(_cmd);
            host.getChild(k)->accept(*this);
            _cmd = oldCmd;
            _splitUpAndApply.setCmd(oldCmd);
            host.accept(_splitUpAndApply);
        }
        }
    }

    // ========= visit const =========

    void caseAt(int, NTree<T> const &) override {
        cerr << "Cannot insert into a const NTree." << endl;
        throw -1;
    }
};

// Global function for convenience
template<class T>
void insert(NTree<T> &tree, int order, int key) {
    NWBTreeInsertVis<T> insertVis(order, key);
    tree.accept(insertVis);
}

#endif
