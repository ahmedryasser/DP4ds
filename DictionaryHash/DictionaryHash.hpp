// File: Hash/Hash.hpp

#ifndef DICTIONARYHASH_HPP
#define DICTIONARYHASH_HPP

#include <iostream> // ostream.
#include <string> // string.
#include <functional>
#include "CAMetrics.hpp"
#include "HashFunctions.hpp"
#include "ADictionary.hpp"
#include "ArrayP.hpp"
#include "ListCSV.hpp"
#include "LCSVclearVis.hpp"
#include "LCSVisEmptyVis.hpp"
#include "LCSVtoStreamVis.hpp"
#include "DictHcontainsVis.hpp"
#include "DictHinsertVis.hpp"
#include "DictHremoveVis.hpp"
using namespace std;

// ========= DictionaryHash =========

template <class K, class V>
class DictionaryHash : public ADictionary<K, V> {
private:
    ArrayP< ListCSV< DictPair<K, V> > *> *_hashTable;
    HashFunction _hashFunction;

public:
    DictionaryHash(int cap, HashFunction hashFunction) :
        _hashTable(new ArrayP< ListCSV< DictPair<K, V> > *>(cap)),
        _hashFunction(hashFunction) {
        for (int i = 0; i < cap; i++) {
            (*_hashTable)[i] = new ListCSV< DictPair<K, V> >();
        }
    }

    ~DictionaryHash() {
    }

    void clear() override {
        for (int i = 0; i < _hashTable->cap(); i++) {
            delete (*_hashTable)[i];
            (*_hashTable)[i] = new ListCSV< DictPair<K, V> >();
        }
    }

    void insert(K const &key, V const &val) override {
        cerr << "HashTable::insert: Exercise for the student." << endl;
        throw -1;
    }

    bool remove(K const &key, V &val) override {
        ListCSV< DictPair<K, V> > *list = (*_hashTable)[_hashFunction(key) % _hashTable->cap()];
        DictHremoveVis<K, V> removeVis(key);
        list->accept(removeVis);
        return removeVis.result(val);
    }

    bool contains(K const &key, V &val) const override {
        cerr << "HashTable::contains: Exercise for the student." << endl;
        throw -1;
    }

    // Post: Sends the entire hash table to os. For each index of the
    // hash table that contains a nonempty chain, outputs that index
    // followed by ": " followed by the chain.

    void toStream(ostream &os) const override {
        cerr << "HashTable::toStream: Exercise for the student." << endl;
        throw -1;
    }
};

#endif
