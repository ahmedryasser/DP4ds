// File: DictionaryBST/DictTinsertVis.hpp

#ifndef DICTTINSERTVIS_HPP_
#define DICTTINSERTVIS_HPP_

#include <iostream>
#include "ADictionary.hpp"
#include "BiTreeCSV.hpp"
using namespace std;

// ========= DictTinsertVis =========
template < class K, class V>
class DictTinsertVis: public ABiTreeCSVVis< DictPair<K, V> > {
private:
    K const &_key; // Input parameter.
    V const &_val; // Input parameter.

public:
    // ========= Constructor =========
    DictTinsertVis(K const &key, V const &val):
        _key(key),
        _val(val) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The host dictionary contains key and its associated value, val.
    void emptyCase(BiTreeCSV< DictPair<K, V> > &host) override {
        DictPair<K, V> pair(_key,_val);
        host.insertRoot(pair);
    }

    void nonEmptyCase(BiTreeCSV< DictPair<K, V> > &host) override {
        if (_key < host.root().key()){
            host.left().accept(*this);
        }
        else if (_key > host.root().key()){
            host.right().accept(*this);
        }
        else{
            DictPair<K,V> pair(host.root().key(), _val);
            host.root() = pair;
        }
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV< DictPair<K, V> > const &host) override {
        cerr << "DictTinsertVis precondition violated: "
             << "Cannot insert into a const tree." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV< DictPair<K, V> > const &host) override {
        cerr << "DictTinsertVis precondition violated: "
             << "Cannot insert into a const tree." << endl;
        throw -1;
    }
};

#endif
